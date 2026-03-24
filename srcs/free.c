#include "malloc.h"

void	fuse_free_blocks(t_zone *zone) {
	t_block *curr = zone->blocks;
	if (!curr->next) // un seul bloc, rien a fusionner
		return ;
	
	while (curr) {
		while (curr->free && curr->next && curr->next->free) {
			curr->size += curr->next->size + sizeof(t_block);
			curr->next = curr->next->next;
		}
		curr = curr->next;
	}
}

void	ft_free(void *ptr) {
	if (!z_tiny && !z_med && !z_tiny)
		return ;
	if (!ptr)
		return ;

	t_block *block = ptr - sizeof(t_block);
	if (block->free)
		return ;

	if (block->size <= MED_MAX_BYTES) {
		t_zone *zone = z_med;
		if (block->size <= TINY_MAX_BYTES)
			zone = z_tiny;
		
		block->free = 1;
		fuse_free_blocks(zone);
	} else {
		t_zone *zone = (void *)block - sizeof(t_zone); // un seul bloc par zone pour la large, donc on peut facilement la remonter
		t_zone *curr = z_big;
		t_zone *previous = NULL;

		while (curr) {
			if (curr == zone) {
				if (!previous) // si pas de precedente, alors c'est la premiere (z_big), on fait de la next la nouvelle premiere
					z_big = curr->next;
				else // sinon, on rattache la precedente a la suivante
					previous->next = curr->next;
			}
			previous = curr;
			curr = curr->next;
		}
	}
}
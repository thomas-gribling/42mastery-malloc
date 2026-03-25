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
	if (!zo[0] && !zo[1] && !zo[2])
		return ;
	if (!ptr)
		return ;

	t_block *block = ptr - sizeof(t_block);
	if (block->free)
		return ;

	if (block->size <= MED_MAX_BYTES) {
		int zone_id = 1;
		if (block->size <= TINY_MAX_BYTES)
			zone_id = 0;
		t_zone *zone = zo[zone_id];
		
		block->free = 1;
		fuse_free_blocks(zone);
		if (is_zone_empty(zone)) {
			munmap(zo[zone_id], zone->size);
			zo[zone_id] = NULL;
		}
	} else {
		t_zone *zone = (void *)block - sizeof(t_zone); // un seul bloc par zone pour la large, donc on peut facilement la remonter
		t_zone *curr = zo[2];
		t_zone *previous = NULL;

		while (curr) {
			if (curr == zone) {
				if (!previous) // si pas de precedente, alors c'est la premiere (z_big), on fait de la next la nouvelle premiere
					zo[2] = curr->next;
				else // sinon, on rattache la precedente a la suivante
					previous->next = curr->next;
				munmap(curr, curr->size + sizeof(t_zone) + sizeof(t_block));
				break ;
			}
			previous = curr;
			curr = curr->next;
		}
	}
}

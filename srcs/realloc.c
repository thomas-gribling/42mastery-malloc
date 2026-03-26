#include "malloc.h"

int	is_allocated(void *ptr) { // il est impossible de fix entierement des conditional jumps provoques par l'user, mais ca permet de les reduire
	t_block *block = ptr - sizeof(t_block);

	if (zo[0]) {
		t_block *curr = zo[0]->blocks;
		while (curr) {
			if (curr == block && !curr->free)
				return 1;
			curr = curr->next;
		}
	}
	if (zo[1]) {
		t_block *curr = zo[1]->blocks;
		while (curr) {
			if (curr == block && !curr->free)
				return 1;
			curr = curr->next;
		}
	}
	if (zo[2]) {
		t_zone *curr = zo[2];
		while (curr) {
			if ((void *)(curr + sizeof(t_zone)) == (void *)block)
				return 1;
			curr = curr->next;
		}
	}
	return 0;
}

void	*alloc_new_ptr(void *ptr, size_t size) { // alloue un nouveau pointeur, copie les donnes et free l'ancien
	char *new_ptr = ft_malloc(size); // void* pas iterable
	for (size_t n = 0; n < size; n++) {
		new_ptr[n] = ((char*)ptr)[n];
	}
	ft_free(ptr);
	return new_ptr;
}

void	*ft_realloc(void *ptr, size_t size) {
	size = (size + 7) & ~7;

	if (!ptr || !is_allocated(ptr))
		return ft_malloc(size);

	t_block *block = ptr - sizeof(t_block);
	if (!block)
		return NULL;
	
	if (size == block->size)
		return ptr;

	// Gerer un potentiel changement de zone
	int zone_id = 2;
	if (block->size <= TINY_MAX_BYTES)
		zone_id = 0;
	else if (block->size <= MED_MAX_BYTES)
		zone_id = 1;
	int target_zone = 2;
	if (size <= TINY_MAX_BYTES)
		target_zone = 0;
	else if (size <= MED_MAX_BYTES)
		target_zone = 1;
	if (zone_id != target_zone)
		return alloc_new_ptr(ptr, size);
	
	// Si on est en zone large
	if (zone_id == 2) { // les mmap ne se suivent pas dans la memoire, pas besoin de reallouer
		t_zone *zone = (void *)block - sizeof(t_zone);
		zone->size = size;
		block->size = size;
		return ptr;
	}
	
	// Si on demande une taille plus petite
	if (size < block->size) {
		if (block->next && block->next->free) { // on rajoute de l'espace libre au bloc adjacent deja free
			t_block *new = (t_block *)((char *)block + sizeof(t_block) + size);
			new->size = block->next->size + (block->size - size);
			new->free = 1;
			new->next = block->next->next;
			block->size = size;
			block->next = new;
			return ptr;
		}
		else if (block->next && !block->next->free && block->size - size >= sizeof(t_block) + 8) { // pas de bloc free adjacent, mais assez de size retiree pour en creer un de taille minimale (8 bytes)
			t_block *new = (t_block *)((char *)block + sizeof(t_block) + size);
			new->size = block->size - size - sizeof(t_block);
			new->free = 1;
			new->next = block->next; // cette fois ce n'est pas une fusion
			block->size = size;
			block->next = new;
			return ptr;
		} else
			return alloc_new_ptr(ptr, size);
	}

	// Verifier s'il y a la place dans un bloc adjacent

	// Dernier cas, simplement alloc_new_ptr()
	return alloc_new_ptr(ptr, size);
}
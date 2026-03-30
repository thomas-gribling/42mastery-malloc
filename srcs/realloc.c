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
			if ((t_block *)(curr + 1) == block)
				return 1;
			curr = curr->next;
		}
	}
	return 0;
}

void	*alloc_new_ptr(void *ptr, size_t size) { // alloue un nouveau pointeur, copie les donnes et free l'ancien
	char *new_ptr = ft_malloc(size); // void* pas iterable
	if (!new_ptr) // pas de place
		return ptr;
	for (size_t n = 0; n < size; n++) {
		new_ptr[n] = ((char*)ptr)[n];
	}
	ft_free(ptr);
	return (void *)new_ptr;
}

void	*ft_realloc(void *ptr, size_t size) {
	if (!ptr || (int)size <= 0)
		return ptr;

	size = (size + 7) & ~7;

	if (!is_allocated(ptr))
		return ft_malloc(size);

	t_block *block = ptr - sizeof(t_block);
	if (!block)
		return ptr;
	
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
	if (zone_id == 2)
		return alloc_new_ptr(ptr, size);
	
	// Si on demande une taille plus petite
	if (size < block->size) {
		if (block->next && block->next->free) { // on rajoute de l'espace libre au bloc adjacent deja free
			t_block *tmp_block = block->next->next;
			size_t tmp_size = block->next->size;
			t_block *new = (t_block *)((char *)block + sizeof(t_block) + size);
			new->size = tmp_size + (block->size - size);
			new->free = 1;
			new->next = tmp_block;
			block->size = size;
			block->next = new;
			return ptr;
		}
		else if (block->next && !block->next->free && block->size - size >= sizeof(t_block) + 8) { // pas de bloc free adjacent, mais assez de size pour en creer un
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
	if (size > block->size) {
		size_t missing_size = size - block->size;
		if (block->next && block->next->free && block->next->size + sizeof(t_block) == missing_size) { // pile assez de place pour absorber le bloc free adjacent
			block->size += missing_size;
			block->next = block->next->next;
			return ptr;
		} else if (block->next && block->next->free && block->next->size >= 8 + missing_size) { // bloc assez grand pour y recuperer de l'espace sans le faire descendre sous le minimum
			t_block *tmp_block = block->next->next; // le nouveau bloc va ecraser block->next, il faut recup les infos avant
			size_t tmp_size = block->next->size;
			t_block *new = (t_block *)((char *)block + sizeof(t_block) + size);
			new->size = tmp_size - missing_size;
			new->free = 1;
			new->next = tmp_block;
			block->size += missing_size;
			block->next = new;
			return ptr;
		} else
			return alloc_new_ptr(ptr, size);
	}

	// Dernier cas, simplement alloc_new_ptr()
	return alloc_new_ptr(ptr, size);
}
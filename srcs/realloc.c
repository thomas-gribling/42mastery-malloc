#include "malloc.h"

int	enough_space_zones(t_block *block, size_t size) {
	return 0; // tmp

	if (!block || !block->next)
		return 0;
	
	size_t missing_size = size - block->size; // la taille supplementaire necessaire
	if (block->next && block->next->free) {
		if (block->size + sizeof(t_block) == missing_size) // cas 1: pile assez de place en prenant le bloc
			return 1;
		// cas 2: plus de place que necessaire, verifier si on a assez de place pour le bloc free qui restera
	}
	return 0;
}

void	*ft_realloc(void *ptr, size_t size) {
	if (!ptr)
		return ft_malloc(size);

	t_block *block = ptr - sizeof(t_block);
	// verifier si on demande un malloc plus petit, ou egal
	// verifier aussi les zones
	int space_state = enough_space_zones(block, size);
	if (space_state == 1) { // s'il y a un bloc adjacent avec pile la place
		block->size += block->next->size + sizeof(t_block);
		block->next = block->next->next;
		return ptr;
	} else if (space_state == 2) { // s'il y a un bloc adjacent avec assez de place

	} else { // sinon, nouveau free + copie des donneess
		char *new_ptr = ft_malloc(size); // un void* n'est pas iterable
		if (!new_ptr)
			return NULL;
		
		for (size_t n = 0; n < size; n++) { // copier les donnees
			new_ptr[n] = ((char*)ptr)[n];
		}
		ft_free(ptr);
		return (void *)new_ptr;
	}
}
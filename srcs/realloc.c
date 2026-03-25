#include "malloc.h"

int	enough_space(t_block *block, size_t size) {
	return 0; //tmp

	if (!block || !block->next)
		return 0;
	
	size_t missing_size = size - block->size;
	if (block->next && block->next->free) {
		// cas 1: pile assez de place en prenant le bloc
		// cas 2: plus de place que necessaire, verifier si on a assez de place pour le bloc free qui restera
	}
	return 0;
}

void	*ft_realloc(void *ptr, size_t size) {
	// gerer le cas ou on demande un realloc plus petit
	// verifier si on a la place dans un bloc free adjacent
	// sinon, nouveau malloc, copier les donnees, nouveau free
	if (!ptr)
		return ft_malloc(size);

	t_block *block = ptr - sizeof(t_block);
	if (enough_space(block, size)) { // s'il y a un bloc adjacent avec assez de place

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
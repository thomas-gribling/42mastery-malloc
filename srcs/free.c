#include "malloc.h"

static void	*find_free_block(t_block *block) { // cherche un bloc free, peu importe sa taille
	while (block) {
		if (block->free)
			return block;
		block = block->next;
	}
	return NULL;
}

void	fuse_block(t_block *block) {
	t_block *free_block = find_free_block(block);

	if (!free_block) { // il n'y a plus d'espace libre, devenir l'espace libre
		block->free = 1;
		// TODO trouver un moyen de le bouger a la fin (un swap en loop jusqu'au bout ?)
	}
	else { // il y a de l'espace libre, fusionner notre bloc avec lui
		block->size += free_block->size;
		block->free = 1;
		block->next = NULL; // TODO ne marche que si le next actuel est notre free_block
	}

}

void	ft_free(void *ptr) {
	t_block *block = ptr - sizeof(t_block);

	if (block->size <= MED_MAX_BYTES) {
		fuse_block(block);
		// TODO si la nouvelle size est egale a la size de la zone, elle est vide, donc la delete (trouver laquelle avec la size)
	} else {
		t_zone *zone = (void *)block - sizeof(t_zone); // un seul block par zone pour la large, donc on peut facilement remonter
		printf("%ld %ld\n", zone->size, block->size);
		zone->blocks->free = 1;
		//munmap(zone, zone->size);
		// TODO remove cette zone de la liste chainee des zones, pour eviter le segfault
		// TODO si c'est la derniere, la zone large devient nulle
	}
}
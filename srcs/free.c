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

	if (!free_block) { // il n'y a plus de bloc free, le devenir. normalement impossible
		printf("ERROR, IMPOSSIBLE CASE\n");
		//block->free = 1;
		// TODO trouver un moyen de le bouger a la fin (un swap en loop jusqu'au bout ?)
	}
	else { // il y a de l'espace libre, fusionner notre bloc avec lui
		block->size += free_block->size + sizeof(t_block);
		block->free = 1;
		block->next = NULL; // TODO ne marche que si le next actuel est notre free_block

		// UTILISER DIFFERENT BLOCS FREE, NE PLUS SE LIMITER A UN SEUL EN FIN DE ZONE

		// modifier directement la memoire libre et relier les deux blocs adjacents a celui la, creerait un vide dans la memoire
		// il faut directement deplacer les blocs
	}

}

void	ft_free(void *ptr) {
	if (!z_tiny && !z_med && !z_tiny)
		return ;
	if (!ptr)
		return ;

	t_block *block = ptr - sizeof(t_block);

	if (block->size <= MED_MAX_BYTES) {
		fuse_block(block);
		if (block->size <= TINY_ZONE_SIZE
				&& z_tiny->size == block->size + sizeof(t_block) + sizeof(t_zone)) { // la zone tiny est vide
			munmap(z_tiny, z_tiny->size);
			z_tiny = NULL;
		}
		else if (block->size > TINY_ZONE_SIZE && block->size <= MED_ZONE_SIZE
				&& z_med->size == block->size + sizeof(t_block) + sizeof(t_zone)) { // la zone tiny est vide
			munmap(z_med, z_med->size);
			z_med = NULL;
		}
		return ;
	} else {
		t_zone *zone = (void *)block - sizeof(t_zone); // un seul block par zone pour la large, donc on peut facilement remonter
		printf("%ld %ld\n", zone->size, block->size);
		zone->blocks->free = 1;
		//munmap(zone, zone->size);
		// TODO remove cette zone de la liste chainee des zones, pour eviter le segfault. rattacher les zones adjancentes et essayer de les deplacer pour eviter le vide
		// TODO si c'est la derniere, la zone large devient nulle
	}
}
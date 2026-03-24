#include "malloc.h"

t_zone *z_tiny;
t_zone *z_med;
t_zone *z_big;

t_zone	*create_zone(size_t zone_size) {
	t_zone *zone;

	zone = mmap(NULL, zone_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (zone == MAP_FAILED)
		return NULL;
	
	zone->size = zone_size;
	zone->next = NULL;

	zone->blocks = (t_block *)((char *)zone + sizeof(t_zone));
	zone->blocks->size = zone_size - sizeof(t_zone) - sizeof(t_block);
	zone->blocks->free = 1;
	zone->blocks->next = NULL;
	
	return zone;
}

static void	*find_free_block(t_zone *zone, size_t size) { // cherche un bloc free assez grand
	t_block *b = zone->blocks;

	while (b) {
		if (b->free && b->size >= size + sizeof(t_block))
			return b;
		if (b->free && b->size == size)
			return b;
		b = b->next;
	}
	return NULL;
}

void split_block(t_block *block, size_t size) {
	t_block *new;
	int space_left = block->size - size - sizeof(t_block);

	if (space_left > 0) { // si plus d'espace, ne pas garder le bloc free
		new = (t_block *)((char *)block + sizeof(t_block) + size);
		new->size = block->size - size - sizeof(t_block);
		new->free = 1;
		new->next = block->next;
	} else
		new = block->next;

	block->size = size;
	block->free = 0;
	block->next = new;
}

void *alloc_to_zone(t_zone **zone, size_t size, size_t zone_size) {
	t_zone *curr_zone = *zone;
	t_block *block;

	if (curr_zone) {
		block = find_free_block(curr_zone, size);
		if (block) {
			if ((block->size >= size + sizeof(t_block)) || (block->size == size)) // inutile ?
				split_block(block, size);
			else
				return NULL;
			return (block + 1);
		}
	}

	curr_zone = create_zone(zone_size);
	if (!curr_zone)
		return NULL;
	split_block(curr_zone->blocks, size);
	*zone = curr_zone;

	return (curr_zone->blocks + 1);

}

void *alloc_to_large(size_t size) { // utiliser le next de t_zone, chaque alloc est une zone qui possede un block unique (prenant toute la taille)
	t_zone *zone;
	zone = mmap(NULL, size + sizeof(t_zone) + sizeof(t_block), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (zone == MAP_FAILED)
		return NULL;
	
	zone->size = size;
	zone->next = NULL;

	zone->blocks = (t_block *)((void *)zone + sizeof(t_zone));
	zone->blocks->size = size;
	zone->blocks->free = 0;
	zone->blocks->next = NULL;

	t_zone *curr = z_big;
	if (!curr)
		z_big = zone;
	while (curr) {
		if (!curr->next) {
			curr->next = zone;
			break;
		}
		else
			curr = curr->next;
	}

	return (zone->blocks + 1);
}

void	*ft_malloc(size_t size) {
	if (size == 0)
		return NULL;
	
	size = (size + 7) & ~7; // aligner la taille du malloc sur un multiple de 8

	if (size <= TINY_MAX_BYTES)
		return alloc_to_zone(&z_tiny, size, TINY_ZONE_SIZE);
	else if (size <= MED_MAX_BYTES)
		return alloc_to_zone(&z_med, size, MED_ZONE_SIZE);
	else
		return alloc_to_large(size);
	return NULL;
}
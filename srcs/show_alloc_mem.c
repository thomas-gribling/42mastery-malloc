#include "malloc.h"

void	ft_putstr(char *s)
{
	int	i = 0;

	while (s[i]) {
		write(0, &s[i], 1);
		i++;
	}
}

void	ft_putaddress(void *ptr) { // todo
	unsigned long address = (unsigned long)(ptr);
	printf("%lu\n", address);
}

void	show_alloc_mem() {
	t_block *curr;

	printf("TINY : %p\n", z_tiny);
	curr = NULL;
	if (z_tiny)
		curr = z_tiny->blocks;
	while (curr) {
		if (!curr->free)
		printf("%p - %p : %ld bytes\n", curr, (curr + curr->size), curr->size);
		curr = curr->next;
	}
	printf("MEDIUM : %p\n", z_med);
	curr = NULL;
	if (z_med)
		curr = z_med->blocks;
	while (curr) {
		printf("%p - %p : %ld bytes\n", curr, (curr + curr->size), curr->size);
		curr = curr->next;
	}
	printf("LARGE : %p\n", z_big);
	curr = NULL;
	if (z_big)
		curr = z_big->blocks;
	while (curr) {
		printf("%p - %p : %ld bytes\n", curr, (curr + curr->size), curr->size);
		curr = curr->next;
	}
}
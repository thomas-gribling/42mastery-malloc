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
	t_zone *curr2;

	curr = NULL;
	if (z_tiny) {
		printf("TINY : %p\n", z_tiny);
		curr = z_tiny->blocks;
		while (curr) {
			if (!curr->free)
				printf("%p - %p : %ld bytes\n", curr, (curr + curr->size), curr->size);
			curr = curr->next;
		}
	}
	curr = NULL;
	if (z_med) {
		printf("MEDIUM : %p\n", z_med);
		curr = z_med->blocks;
		while (curr) {
			if (!curr->free)
				printf("%p - %p : %ld bytes\n", curr, (curr + curr->size), curr->size);
			curr = curr->next;
		}
	}
	curr2 = NULL;
	if (z_big) {
		printf("LARGE : %p\n", z_big);
		curr2 = z_big;
		while (curr2) {
			printf("%p - %p : %ld bytes\n", curr2, (curr2 + curr2->size), curr2->size);
			curr2 = curr2->next;
		}
	}

	if (!z_tiny && !z_med && !z_big)
		printf("No memory allocated.\n");
}
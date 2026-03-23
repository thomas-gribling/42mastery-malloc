#include "srcs/malloc.h"

#include <string.h>

void	test_hundred_malloc() { // TODO (need free)
	// Test the 100 mallocs minimum per zone
	/*for (int i = 0; i < 100; i++) {
		void *ptr = ft_malloc(TINY_MAX_BYTES);
		if (!ptr) {
			printf("ERROR! Failed malloc %d/100 (no space left in zone)\n", i + 1);
			return 1;
		}
	}
	printf("The 100 mallocs were successfull.\n");
	return 0;*/
}

int main(void) {

	/*ft_malloc(0);
	ft_malloc(1);
	ft_malloc(7);
	ft_malloc(9);
	ft_malloc(17);
	ft_malloc(TINY_MAX_BYTES + 1);
	ft_malloc(TINY_MAX_BYTES + 9);
	ft_malloc(TINY_MAX_BYTES + 17);
	ft_malloc(MED_MAX_BYTES + 1);
	ft_malloc(MED_MAX_BYTES + 9);
	ft_malloc(MED_MAX_BYTES + 17);*/
	void *a = ft_malloc(1);
	void *b = ft_malloc(1);
	show_alloc_mem();
	ft_free(b);
	ft_free(a);
	show_alloc_mem();

	a = ft_malloc(TINY_MAX_BYTES + 1);
	b = ft_malloc(TINY_MAX_BYTES + 1);
	show_alloc_mem();
	ft_free(b);
	ft_free(a);
	show_alloc_mem();
	return 0;
}
#include "srcs/malloc.h"

#include <string.h>

void	test_hundred_malloc() {
	void *ptr[100];

	for (int i = 0; i < 100; i++) {
		ptr[i] = ft_malloc(TINY_MAX_BYTES);
		if (!ptr[i])
			write(2, "Error!\n", 6);
	}
	for (int i = 0; i < 100; i++) {
		ft_free(ptr[i]);
		ptr[i] = ft_malloc(MED_MAX_BYTES);
		if (!ptr[i])
			write(2, "Error!\n", 6);
	}
	for (int i = 0; i < 100; i++) {
		ft_free(ptr[i]);
		ptr[i] = ft_malloc(MED_MAX_BYTES * 10);
		if (!ptr[i])
			write(2, "Error!\n", 6);
	}
	for (int i = 0; i < 100; i++) {
		ft_free(ptr[i]);
	}
	show_alloc_mem();
	write(1, "\n", 1);
}

void	test_speed_thousand_malloc() {
	void *ptr[3];

	for (int i = 0; i < 1000; i++) {
		ptr[0] = ft_malloc(TINY_MAX_BYTES);
		ptr[1] = ft_malloc(MED_MAX_BYTES);
		ptr[2] = ft_malloc(MED_MAX_BYTES * 10);
		ft_free(ptr[0]);
		ft_free(ptr[1]);
		ft_free(ptr[2]);
	}
	show_alloc_mem();
	write(1, "\n", 1);
}

void	test_double() {
	void *a = ft_malloc(1);
	void *b = ft_malloc(1);
	show_alloc_mem();
	ft_free(a);
	show_alloc_mem();
	a = ft_malloc(1);
	show_alloc_mem();
	ft_free(b);
	show_alloc_mem();
	ft_free(a);
	show_alloc_mem();
	write(1, "\n", 1);

	a = ft_malloc(TINY_MAX_BYTES + 1);
	b = ft_malloc(TINY_MAX_BYTES + 1);
	show_alloc_mem();
	ft_free(a);
	show_alloc_mem();
	a = ft_malloc(TINY_MAX_BYTES + 1);
	show_alloc_mem();
	ft_free(b);
	show_alloc_mem();
	ft_free(a);
	show_alloc_mem();
	write(1, "\n", 1);

	a = ft_malloc(MED_MAX_BYTES + 1);
	b = ft_malloc(MED_MAX_BYTES + 1);
	show_alloc_mem();
	ft_free(a);
	show_alloc_mem();
	a = ft_malloc(MED_MAX_BYTES + 1);
	show_alloc_mem();
	ft_free(b);
	show_alloc_mem();
	ft_free(a);
	show_alloc_mem();
	write(1, "\n", 1);
}

void test_triple() {
	void *a = ft_malloc(1);
	void *b = ft_malloc(1);
	void *c = ft_malloc(1);
	show_alloc_mem();
	ft_free(b);
	show_alloc_mem();
	b = ft_malloc(1);
	show_alloc_mem();
	ft_free(a);
	show_alloc_mem();
	ft_free(b);
	show_alloc_mem();
	ft_free(c);
	show_alloc_mem();
	write(1, "\n", 1);

	a = ft_malloc(TINY_MAX_BYTES + 1);
	b = ft_malloc(TINY_MAX_BYTES + 1);
	c = ft_malloc(TINY_MAX_BYTES + 1);
	show_alloc_mem();
	ft_free(b);
	show_alloc_mem();
	b = ft_malloc(TINY_MAX_BYTES + 1);
	show_alloc_mem();
	ft_free(a);
	show_alloc_mem();
	ft_free(b);
	show_alloc_mem();
	ft_free(c);
	show_alloc_mem();
	write(1, "\n", 1);

	a = ft_malloc(MED_MAX_BYTES + 1);
	b = ft_malloc(MED_MAX_BYTES + 1);
	c = ft_malloc(MED_MAX_BYTES + 1);
	show_alloc_mem();
	ft_free(b);
	show_alloc_mem();
	b = ft_malloc(MED_MAX_BYTES + 1);
	show_alloc_mem();
	ft_free(a);
	show_alloc_mem();
	ft_free(b);
	show_alloc_mem();
	ft_free(c);
	show_alloc_mem();
	write(1, "\n", 1);
}

int main(void) {

	/*test_hundred_malloc();
	//test_speed_thousand_malloc();
	
	test_double();
	test_triple();*/

	// Realloc quand pas assez de place
	char *a = NULL;
	char *b = NULL;
	a = ft_realloc(a, 5); // essayer de fix pour un undefine pointer
	b = ft_realloc(b, 5);
	show_alloc_mem();
	a = ft_realloc(a, 9);
	show_alloc_mem();
	ft_free(a);
	ft_free(b);
	show_alloc_mem();
	write(1, "\n", 1);

	// Realloc quand pile la place
	a = NULL;
	b = NULL;
	char *c = NULL;
	a = ft_realloc(a, 1);
	b = ft_realloc(b, 1);
	c = ft_realloc(c, 1);
	show_alloc_mem();
	ft_free(b);
	show_alloc_mem();
	a = ft_realloc(a, 40);
	show_alloc_mem();
	ft_free(a);
	ft_free(c);
	show_alloc_mem();
	write(1, "\n", 1);

	// Realloc quand assez de place mais pas pour le bloc
	a = NULL;
	b = NULL;
	c = NULL;
	a = ft_realloc(a, 1);
	b = ft_realloc(b, 1);
	c = ft_realloc(c, 1);
	show_alloc_mem();
	ft_free(b);
	show_alloc_mem();
	a = ft_realloc(a, 9);
	show_alloc_mem();
	ft_free(a);
	ft_free(c);
	show_alloc_mem();
	write(1, "\n", 1);

	return 0;
}
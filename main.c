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

	test_hundred_malloc();
	
	test_double();
	test_triple();

	return 0;
}

/*
TODO LIST:
- transformer les 3 globals en un seul array
- realloc
*/
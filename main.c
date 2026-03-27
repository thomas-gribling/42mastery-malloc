#include "srcs/malloc.h"

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

void	test_triple() {
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

void	test_realloc_basic() {
	// Realloc dans une autre zone
	{
		void *a = ft_malloc(MED_MAX_BYTES);
		void *b = ft_malloc(TINY_MAX_BYTES);
		show_alloc_mem();
		a = ft_realloc(a, 1);
		show_alloc_mem();
		b = ft_realloc(b, TINY_MAX_BYTES + 1);
		show_alloc_mem();
		ft_free(a);
		ft_free(b);
		show_alloc_mem();
		write(1, "\n", 1);
	}

	// Realloc dans la zone large
	{
		void *a = ft_malloc(MED_MAX_BYTES * 10);
		void *b = ft_malloc(MED_MAX_BYTES * 10);
		show_alloc_mem();
		a = ft_realloc(a, MED_MAX_BYTES * 20);
		show_alloc_mem();
		b = ft_realloc(b, MED_MAX_BYTES + 1);
		show_alloc_mem();
		ft_free(a);
		ft_free(b);
		show_alloc_mem();
		write(1, "\n", 1);
	}
}

void	test_realloc_smaller() {
	// Realloc plus petit avec bloc free adjacent
	{
		void *a = ft_malloc(8 * 2);
		void *b = ft_malloc(TINY_MAX_BYTES);
		void *c = ft_malloc(8);
		show_alloc_mem();
		ft_free(b);
		show_alloc_mem();
		a = ft_realloc(a, 8);
		show_alloc_mem();
		ft_free(a);
		ft_free(c);
		show_alloc_mem();
		write(1, "\n", 1);
	}

	// Realloc plus petit sans free adjacent mais suffisamment grand pour split en un nouveau free
	{
		void *a = ft_malloc(8 * 2 + 32);
		void *b = ft_malloc(8);
		show_alloc_mem();
		a = ft_realloc(a, 8 * 2);
		show_alloc_mem();
		ft_free(a);
		ft_free(b);
		show_alloc_mem();
		write(1, "\n", 1);
	}

	// Realloc plus petit sans bloc free adjacent
	{
		void *a = ft_malloc(8 * 2);
		void *b = ft_malloc(8);
		show_alloc_mem();
		a = ft_realloc(a, 8);
		show_alloc_mem();
		ft_free(a);
		ft_free(b);
		show_alloc_mem();
		write(1, "\n", 1);
	}
}

void	test_realloc_bigger () {
	// Realloc plus grand avec bloc free adjacent (pile la place)
	{
		void *a = ft_malloc(8);
		void *b = ft_malloc(8);
		void *c = ft_malloc(8);
		show_alloc_mem();
		ft_free(b);
		show_alloc_mem();
		a = ft_realloc(a, 8 + 32);
		show_alloc_mem();
		ft_free(a);
		ft_free(c);
		show_alloc_mem();
		write(1, "\n", 1);
	}

	// Realloc plus grand avec bloc free adjacent (plus grand que necessaire et suffisament pour lui prendre)
	{
		void *a = ft_malloc(8);
		void *b = ft_malloc(8 * 2);
		void *c = ft_malloc(8);
		show_alloc_mem();
		ft_free(b);
		show_alloc_mem();
		a = ft_realloc(a, 8 * 2);
		show_alloc_mem();
		ft_free(a);
		ft_free(c);
		show_alloc_mem();
		write(1, "\n", 1);
	}

	// Realloc plus grand quand pas assez de place
	{
		void *a = ft_malloc(8 * 2);
		void *b = ft_malloc(8);
		show_alloc_mem();
		a = ft_realloc(a, 8);
		show_alloc_mem();
		ft_free(a);
		ft_free(b);
		show_alloc_mem();
		write(1, "\n", 1);
	}
}

int main(void) {

	test_hundred_malloc();
	//test_speed_thousand_malloc();
	
	test_double();
	test_triple();
	
	/*test_realloc_basic();
	test_realloc_smaller();
	test_realloc_bigger();*/

	return 0;
}
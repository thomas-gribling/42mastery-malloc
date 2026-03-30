#include "tests.h"

static void	print_memory() { // changer rapidement la fonction de print utilisee pendant la correc
	show_alloc_mem();
}

static int	ft_puterr(char *s) {
	int	i = -1;
	while (s[++i])
		write(2, &s[i], 1);
	return 1;
}

int	test_hundred_malloc() {
	void *ptr[100];

	for (int i = 0; i < 100; i++) {
		ptr[i] = ft_malloc(TINY_MAX_BYTES);
		if (!ptr[i])
			return ft_puterr("Error! Not enough space in small zone!\n");
	}
	for (int i = 0; i < 100; i++) {
		ft_free(ptr[i]);
		ptr[i] = ft_malloc(MED_MAX_BYTES);
		if (!ptr[i])
			return ft_puterr("Error! Not enough space in medium zone!\n");
	}
	for (int i = 0; i < 100; i++) {
		ft_free(ptr[i]);
		ptr[i] = ft_malloc(MED_MAX_BYTES * 10);
		if (!ptr[i])
			return ft_puterr("Error! Not enough space in large zone!\n");
	}
	for (int i = 0; i < 100; i++) {
		ft_free(ptr[i]);
	}
	print_memory();
	write(1, "\n", 1);
	return 0;
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
	print_memory();
	write(1, "\n", 1);
}

void	test_double() {
	void *a = ft_malloc(1);
	void *b = ft_malloc(1);
	print_memory();
	ft_free(a);
	print_memory();
	a = ft_malloc(1);
	print_memory();
	ft_free(b);
	print_memory();
	ft_free(a);
	print_memory();
	write(1, "\n", 1);

	a = ft_malloc(TINY_MAX_BYTES + 1);
	b = ft_malloc(TINY_MAX_BYTES + 1);
	print_memory();
	ft_free(a);
	print_memory();
	a = ft_malloc(TINY_MAX_BYTES + 1);
	print_memory();
	ft_free(b);
	print_memory();
	ft_free(a);
	print_memory();
	write(1, "\n", 1);

	a = ft_malloc(MED_MAX_BYTES + 1);
	b = ft_malloc(MED_MAX_BYTES + 1);
	print_memory();
	ft_free(a);
	print_memory();
	a = ft_malloc(MED_MAX_BYTES + 1);
	print_memory();
	ft_free(b);
	print_memory();
	ft_free(a);
	print_memory();
	write(1, "\n", 1);
}

void	test_triple() {
	void *a = ft_malloc(1);
	void *b = ft_malloc(1);
	void *c = ft_malloc(1);
	print_memory();
	ft_free(b);
	print_memory();
	b = ft_malloc(1);
	print_memory();
	ft_free(a);
	print_memory();
	ft_free(b);
	print_memory();
	ft_free(c);
	print_memory();
	write(1, "\n", 1);

	a = ft_malloc(TINY_MAX_BYTES + 1);
	b = ft_malloc(TINY_MAX_BYTES + 1);
	c = ft_malloc(TINY_MAX_BYTES + 1);
	print_memory();
	ft_free(b);
	print_memory();
	b = ft_malloc(TINY_MAX_BYTES + 1);
	print_memory();
	ft_free(a);
	print_memory();
	ft_free(b);
	print_memory();
	ft_free(c);
	print_memory();
	write(1, "\n", 1);

	a = ft_malloc(MED_MAX_BYTES + 1);
	b = ft_malloc(MED_MAX_BYTES + 1);
	c = ft_malloc(MED_MAX_BYTES + 1);
	print_memory();
	ft_free(b);
	print_memory();
	b = ft_malloc(MED_MAX_BYTES + 1);
	print_memory();
	ft_free(a);
	print_memory();
	ft_free(b);
	print_memory();
	ft_free(c);
	print_memory();
	write(1, "\n", 1);
}

void	test_realloc_basic() {
	// Realloc dans une autre zone
	{
		void *a = ft_malloc(TINY_MAX_BYTES);
		void *b = ft_malloc(MED_MAX_BYTES);
		void *c = ft_malloc(MED_MAX_BYTES * 10);
		print_memory();
		a = ft_realloc(a, TINY_MAX_BYTES + 1);
		print_memory();
		b = ft_realloc(b, MED_MAX_BYTES + 1);
		print_memory();
		c = ft_realloc(c, 1);
		print_memory();
		ft_free(a);
		ft_free(b);
		ft_free(c);
		print_memory();
		write(1, "\n", 1);
	}

	// Realloc dans la zone large
	{
		void *a = ft_malloc(MED_MAX_BYTES * 10);
		void *b = ft_malloc(MED_MAX_BYTES * 10);
		print_memory();
		a = ft_realloc(a, MED_MAX_BYTES * 20);
		print_memory();
		b = ft_realloc(b, MED_MAX_BYTES + 1);
		print_memory();
		ft_free(a);
		ft_free(b);
		print_memory();
		write(1, "\n", 1);
	}
}

void	test_realloc_smaller() {
	// Realloc plus petit avec bloc free adjacent
	{
		void *a = ft_malloc(8 * 2);
		void *b = ft_malloc(TINY_MAX_BYTES);
		void *c = ft_malloc(8);
		print_memory();
		ft_free(b);
		print_memory();
		a = ft_realloc(a, 8);
		print_memory();
		ft_free(a);
		ft_free(c);
		print_memory();
		write(1, "\n", 1);
	}

	// Realloc plus petit sans free adjacent mais suffisamment grand pour split en un nouveau free
	{
		void *a = ft_malloc(8 * 2 + 32);
		void *b = ft_malloc(8);
		print_memory();
		a = ft_realloc(a, 8 * 2);
		print_memory();
		ft_free(a);
		ft_free(b);
		print_memory();
		write(1, "\n", 1);
	}

	// Realloc plus petit sans bloc free adjacent
	{
		void *a = ft_malloc(8 * 2);
		void *b = ft_malloc(8);
		print_memory();
		a = ft_realloc(a, 8);
		print_memory();
		ft_free(a);
		ft_free(b);
		print_memory();
		write(1, "\n", 1);
	}
}

void	test_realloc_bigger () {
	// Realloc plus grand avec bloc free adjacent (pile la place)
	{
		void *a = ft_malloc(8);
		void *b = ft_malloc(8);
		void *c = ft_malloc(8);
		print_memory();
		ft_free(b);
		print_memory();
		a = ft_realloc(a, 8 + 32);
		print_memory();
		ft_free(a);
		ft_free(c);
		print_memory();
		write(1, "\n", 1);
	}

	// Realloc plus grand avec bloc free adjacent (plus grand que necessaire et suffisament pour lui prendre)
	{
		void *a = ft_malloc(8);
		void *b = ft_malloc(8 * 2);
		void *c = ft_malloc(8);
		print_memory();
		ft_free(b);
		print_memory();
		a = ft_realloc(a, 8 * 2);
		print_memory();
		ft_free(a);
		ft_free(c);
		print_memory();
		write(1, "\n", 1);
	}

	// Realloc plus grand quand pas assez de place
	{
		void *a = ft_malloc(8 * 2);
		void *b = ft_malloc(8);
		print_memory();
		a = ft_realloc(a, 8);
		print_memory();
		ft_free(a);
		ft_free(b);
		print_memory();
		write(1, "\n", 1);
	}
}

void	test_failing_cases() {
	printf("%p\n", ft_malloc(-13264));
	printf("%p\n", ft_malloc(-1320154));
	printf("%p\n", ft_malloc(-1));
	printf("%p\n", ft_malloc(0));

	void *ptr = ft_malloc(8);
	printf("%p:%p\n", ptr, ft_realloc(ptr, -15165));
	printf("%p:%p\n", ptr, ft_realloc(ptr, -15745745));
	printf("%p:%p\n", ptr, ft_realloc(ptr, -1));
	printf("%p:%p\n", ptr, ft_realloc(ptr, 0));

	ft_free(ptr);
	print_memory();
	write(1, "\n", 1);
}

void	test_zones_limits() {
	{
		size_t max_ptrs = TINY_ZONE_SIZE / TINY_MAX_BYTES;
		void *ptr[max_ptrs];
		for (size_t n = 0; n < max_ptrs; n++) {
			ptr[n] = ft_malloc(TINY_MAX_BYTES);
		}
		void *last_ptr = ft_malloc(TINY_MAX_BYTES - 8);

		print_memory(); // checker si la zone est bien full
		printf("%p\n", ft_malloc(8)); // doit printf (nil) car plus de place
		printf("%p:%p\n", last_ptr, ft_realloc(last_ptr, TINY_MAX_BYTES)); // zone complete, doit montrer deux fois la meme addresse
		printf("%p:%p\n", last_ptr, ft_realloc(last_ptr, 8)); // idem

		ft_free(last_ptr);
		for (size_t n = 0; n < max_ptrs; n++) {
			ft_free(ptr[n]);
		}
		print_memory();
		write(1, "\n", 1);
	}
	{
		size_t max_ptrs = MED_ZONE_SIZE / MED_MAX_BYTES - 3;
		void *ptr[max_ptrs];
		for (size_t n = 0; n < max_ptrs - 1; n++) {
			ptr[n] = ft_malloc(MED_MAX_BYTES);
		}
		ptr[max_ptrs - 1] = ft_malloc(1024);
		void *last_ptr = ft_malloc(1048);

		print_memory();
		printf("%p\n", ft_malloc(TINY_MAX_BYTES + 8));
		printf("%p:%p\n", last_ptr, ft_realloc(last_ptr, MED_MAX_BYTES));
		printf("%p:%p\n", last_ptr, ft_realloc(last_ptr, TINY_MAX_BYTES + 8));
		
		ft_free(last_ptr);
		for (size_t n = 0; n < max_ptrs; n++) {
			ft_free(ptr[n]);
		}
		print_memory();
		write(1, "\n", 1);
	}
}

void	test_free_null_nalloc() {
	void *ptr;
	ft_free(ptr);
	ft_free(NULL);

	void *p1 = ft_malloc(8);
	void *p2 = ft_malloc(TINY_MAX_BYTES + 8);
	void *p3 = ft_malloc(MED_MAX_BYTES + 8);
	ft_free(ptr);
	ft_free(NULL);

	print_memory();
	ft_free(p1);
	ft_free(p1);
	ft_free(p2);
	ft_free(p2);
	ft_free(p3);
	ft_free(p3);
	print_memory();
	write(1, "\n", 1);
}

void	test_realloc_null_nalloc() {
	void *ptr;
	printf("%p:", ptr);

	ptr = ft_realloc(ptr, 8);
	printf("%p\n", ptr);
	printf("%p\n", ft_realloc(NULL, 8));

	ft_free(ptr);
	print_memory();
	write(1, "\n", 1);
}

void	show_alloc_mem_debug() { // DEBUG VERSION
	t_block *curr;
	t_zone *curr2;

	if (is_zone_empty(zo[0]) && is_zone_empty(zo[1]) && is_zone_empty(zo[2])) {
		ft_putstr("No memory allocated.\n\n");
		return ;
	}

	size_t total_size = 0;
	curr = NULL;
	if (!is_zone_empty(zo[0])) {
		ft_putstr("TINY : ");
		ft_putaddress((unsigned long)zo[0], 1);

		ft_putstr(" (size = ");
		ft_putsize(zo[0]->size);
		ft_putstr(" bytes)");

		ft_putstr("\n");

		ft_putaddress((unsigned long)((char *)zo[0]), 1);
		ft_putstr(" - ");
		ft_putaddress((unsigned long)((char *)zo[0] + sizeof(t_zone) - 1), 1);
		ft_putstr(" : ");
		ft_putsize(sizeof(t_zone));
		ft_putstr(" bytes (ZONE)\n");

		curr = zo[0]->blocks;
		while (curr) {
			ft_putaddress((unsigned long)((char *)curr), 1);
			ft_putstr(" - ");
			ft_putaddress((unsigned long)((char *)curr + sizeof(t_block) - 1), 1);
			ft_putstr(" : ");
			ft_putsize(sizeof(t_block));
			ft_putstr(" bytes (BLOCK)\n");
			if (!curr->free) {
				ft_putaddress((unsigned long)((char *)curr + sizeof(t_block)), 1);
				ft_putstr(" - ");
				ft_putaddress((unsigned long)((char *)curr + sizeof(t_block) + curr->size - 1), 1);
				ft_putstr(" : ");
				ft_putsize(curr->size);
				ft_putstr(" bytes\n");
				total_size += curr->size;
			} else { // temporary, shows free blocks
				ft_putaddress((unsigned long)((char *)curr + sizeof(t_block)), 1);
				ft_putstr(" - ");
				ft_putaddress((unsigned long)((char *)curr + sizeof(t_block) + curr->size - 1), 1);
				ft_putstr(" : ");
				ft_putsize(curr->size);
				ft_putstr(" bytes (FREE)\n");
			}
			curr = curr->next;
		}
	}

	curr = NULL;
	if (!is_zone_empty(zo[1])) {
		ft_putstr("MEDIUM : ");
		ft_putaddress((unsigned long)zo[1], 1);

		ft_putstr(" (size = ");
		ft_putsize(zo[1]->size);
		ft_putstr(" bytes)");

		ft_putstr("\n");

		ft_putaddress((unsigned long)((char *)zo[1]), 1);
		ft_putstr(" - ");
		ft_putaddress((unsigned long)((char *)zo[1] + sizeof(t_zone) - 1), 1);
		ft_putstr(" : ");
		ft_putsize(sizeof(t_zone));
		ft_putstr(" bytes (ZONE)\n");

		curr = zo[1]->blocks;
		while (curr) {
			ft_putaddress((unsigned long)((char *)curr), 1);
			ft_putstr(" - ");
			ft_putaddress((unsigned long)((char *)curr + sizeof(t_block) - 1), 1);
			ft_putstr(" : ");
			ft_putsize(sizeof(t_block));
			ft_putstr(" bytes (BLOCK)\n");
			if (!curr->free) {
				ft_putaddress((unsigned long)((char *)curr + sizeof(t_block)), 1);
				ft_putstr(" - ");
				ft_putaddress((unsigned long)((char *)curr + sizeof(t_block) + curr->size - 1), 1);
				ft_putstr(" : ");
				ft_putsize(curr->size);
				ft_putstr(" bytes\n");
				total_size += curr->size;
			} else { // temporary, shows free blocks
				ft_putaddress((unsigned long)((char *)curr + sizeof(t_block)), 1);
				ft_putstr(" - ");
				ft_putaddress((unsigned long)((char *)curr + sizeof(t_block) + curr->size - 1), 1);
				ft_putstr(" : ");
				ft_putsize(curr->size);
				ft_putstr(" bytes (FREE)\n");
			}
			curr = curr->next;
		}
	}

	curr2 = NULL;
	if (!is_zone_empty(zo[2])) {
		ft_putstr("LARGE : ");
		ft_putaddress((unsigned long)zo[2], 1);
		ft_putstr("\n");
		curr2 = zo[2];
		while (curr2) {
			ft_putaddress((unsigned long)((char *)curr2), 1);
			ft_putstr(" - ");
			ft_putaddress((unsigned long)((char *)curr2 + sizeof(t_zone) - 1), 1);
			ft_putstr(" : ");
			ft_putsize(sizeof(t_zone));
			ft_putstr(" bytes (ZONE)\n");
			ft_putaddress((unsigned long)((char *)curr2->blocks), 1);
			ft_putstr(" - ");
			ft_putaddress((unsigned long)((char *)curr2->blocks + sizeof(t_block) - 1), 1);
			ft_putstr(" : ");
			ft_putsize(sizeof(t_block));
			ft_putstr(" bytes (BLOCK)\n");
			if (!curr2->blocks->free) {
				ft_putaddress((unsigned long)((char *)curr2 + sizeof(t_zone) + sizeof(t_block)), 1);
				ft_putstr(" - ");
				ft_putaddress((unsigned long)((char *)curr2 + sizeof(t_zone) + sizeof(t_block) + curr2->size - 1), 1);
				ft_putstr(" : ");
				ft_putsize(curr2->size);
				ft_putstr(" bytes\n");
				total_size += curr2->size;
			}
			curr2 = curr2->next;
		}
	}

	ft_putstr("Total : ");
	ft_putsize(total_size);
	ft_putstr(" bytes\n\n");
}
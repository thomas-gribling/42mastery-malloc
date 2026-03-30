#include "tests.h"

static void	print_memory() { // changer rapidement la fonction de print utilisee pendant la correc
	show_alloc_mem_debug();
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
		ptr[i] = malloc(TINY_MAX_BYTES);
		if (!ptr[i])
			return ft_puterr("Error! Not enough space in small zone!\n");
	}
	for (int i = 0; i < 100; i++) {
		free(ptr[i]);
		ptr[i] = malloc(MED_MAX_BYTES);
		if (!ptr[i])
			return ft_puterr("Error! Not enough space in medium zone!\n");
	}
	for (int i = 0; i < 100; i++) {
		free(ptr[i]);
		ptr[i] = malloc(MED_MAX_BYTES * 10);
		if (!ptr[i])
			return ft_puterr("Error! Not enough space in large zone!\n");
	}
	for (int i = 0; i < 100; i++) {
		free(ptr[i]);
	}
	print_memory();
	write(1, "\n", 1);
	return 0;
}

void	test_speed_thousand_malloc() {
	void *ptr[3];

	for (int i = 0; i < 1000; i++) {
		ptr[0] = malloc(TINY_MAX_BYTES);
		ptr[1] = malloc(MED_MAX_BYTES);
		ptr[2] = malloc(MED_MAX_BYTES * 10);
		free(ptr[0]);
		free(ptr[1]);
		free(ptr[2]);
	}
	print_memory();
	write(1, "\n", 1);
}

void	test_double() {
	void *a = malloc(1);
	void *b = malloc(1);
	print_memory();
	free(a);
	print_memory();
	a = malloc(1);
	print_memory();
	free(b);
	print_memory();
	free(a);
	print_memory();
	write(1, "\n", 1);

	a = malloc(TINY_MAX_BYTES + 1);
	b = malloc(TINY_MAX_BYTES + 1);
	print_memory();
	free(a);
	print_memory();
	a = malloc(TINY_MAX_BYTES + 1);
	print_memory();
	free(b);
	print_memory();
	free(a);
	print_memory();
	write(1, "\n", 1);

	a = malloc(MED_MAX_BYTES + 1);
	b = malloc(MED_MAX_BYTES + 1);
	print_memory();
	free(a);
	print_memory();
	a = malloc(MED_MAX_BYTES + 1);
	print_memory();
	free(b);
	print_memory();
	free(a);
	print_memory();
	write(1, "\n", 1);
}

void	test_triple() {
	void *a = malloc(1);
	void *b = malloc(1);
	void *c = malloc(1);
	print_memory();
	free(b);
	print_memory();
	b = malloc(1);
	print_memory();
	free(a);
	print_memory();
	free(b);
	print_memory();
	free(c);
	print_memory();
	write(1, "\n", 1);

	a = malloc(TINY_MAX_BYTES + 1);
	b = malloc(TINY_MAX_BYTES + 1);
	c = malloc(TINY_MAX_BYTES + 1);
	print_memory();
	free(b);
	print_memory();
	b = malloc(TINY_MAX_BYTES + 1);
	print_memory();
	free(a);
	print_memory();
	free(b);
	print_memory();
	free(c);
	print_memory();
	write(1, "\n", 1);

	a = malloc(MED_MAX_BYTES + 1);
	b = malloc(MED_MAX_BYTES + 1);
	c = malloc(MED_MAX_BYTES + 1);
	print_memory();
	free(b);
	print_memory();
	b = malloc(MED_MAX_BYTES + 1);
	print_memory();
	free(a);
	print_memory();
	free(b);
	print_memory();
	free(c);
	print_memory();
	write(1, "\n", 1);
}

void	test_realloc_basic() {
	// Realloc dans une autre zone
	{
		void *a = malloc(TINY_MAX_BYTES);
		void *b = malloc(MED_MAX_BYTES);
		void *c = malloc(MED_MAX_BYTES * 10);
		print_memory();
		a = realloc(a, TINY_MAX_BYTES + 1);
		print_memory();
		b = realloc(b, MED_MAX_BYTES + 1);
		print_memory();
		c = realloc(c, 1);
		print_memory();
		free(a);
		free(b);
		free(c);
		print_memory();
		write(1, "\n", 1);
	}

	// Realloc dans la zone large
	{
		void *a = malloc(MED_MAX_BYTES * 10);
		void *b = malloc(MED_MAX_BYTES * 10);
		print_memory();
		a = realloc(a, MED_MAX_BYTES * 20);
		print_memory();
		b = realloc(b, MED_MAX_BYTES + 1);
		print_memory();
		free(a);
		free(b);
		print_memory();
		write(1, "\n", 1);
	}
}

void	test_realloc_smaller() {
	// Realloc plus petit avec bloc free adjacent
	{
		void *a = malloc(8 * 2);
		void *b = malloc(TINY_MAX_BYTES);
		void *c = malloc(8);
		print_memory();
		free(b);
		print_memory();
		a = realloc(a, 8);
		print_memory();
		free(a);
		free(c);
		print_memory();
		write(1, "\n", 1);
	}

	// Realloc plus petit sans free adjacent mais suffisamment grand pour split en un nouveau free
	{
		void *a = malloc(8 * 2 + 32);
		void *b = malloc(8);
		print_memory();
		a = realloc(a, 8 * 2);
		print_memory();
		free(a);
		free(b);
		print_memory();
		write(1, "\n", 1);
	}

	// Realloc plus petit sans bloc free adjacent
	{
		void *a = malloc(8 * 2);
		void *b = malloc(8);
		print_memory();
		a = realloc(a, 8);
		print_memory();
		free(a);
		free(b);
		print_memory();
		write(1, "\n", 1);
	}
}

void	test_realloc_bigger () {
	// Realloc plus grand avec bloc free adjacent (pile la place)
	{
		void *a = malloc(8);
		void *b = malloc(8);
		void *c = malloc(8);
		print_memory();
		free(b);
		print_memory();
		a = realloc(a, 8 + 32);
		print_memory();
		free(a);
		free(c);
		print_memory();
		write(1, "\n", 1);
	}

	// Realloc plus grand avec bloc free adjacent (plus grand que necessaire et suffisament pour lui prendre)
	{
		void *a = malloc(8);
		void *b = malloc(8 * 2);
		void *c = malloc(8);
		print_memory();
		free(b);
		print_memory();
		a = realloc(a, 8 * 2);
		print_memory();
		free(a);
		free(c);
		print_memory();
		write(1, "\n", 1);
	}

	// Realloc plus grand quand pas assez de place
	{
		void *a = malloc(8);
		void *b = malloc(8);
		print_memory();
		a = realloc(a, 8 * 2);
		print_memory();
		free(a);
		free(b);
		print_memory();
		write(1, "\n", 1);
	}
}

void	test_failing_cases() {
	ft_putaddress((unsigned long)malloc(-13264), 1);
	ft_putstr("\n");
	ft_putaddress((unsigned long)malloc(-1320154), 1);
	ft_putstr("\n");
	ft_putaddress((unsigned long)malloc(-1), 1);
	ft_putstr("\n");
	ft_putaddress((unsigned long)malloc(0), 1);
	ft_putstr("\n");

	void *ptr = malloc(8);
	ft_putaddress((unsigned long)ptr, 1);
	ft_putstr(":");
	ft_putaddress((unsigned long)realloc(ptr, -15165), 1);
	ft_putstr("\n");
	ft_putaddress((unsigned long)ptr, 1);
	ft_putstr(":");
	ft_putaddress((unsigned long)realloc(ptr, -15745745), 1);
	ft_putstr("\n");
	ft_putaddress((unsigned long)ptr, 1);
	ft_putstr(":");
	ft_putaddress((unsigned long)realloc(ptr, -1), 1);
	ft_putstr("\n");
	ft_putaddress((unsigned long)ptr, 1);
	ft_putstr(":");
	ft_putaddress((unsigned long)realloc(ptr, 0), 1);
	ft_putstr("\n");

	free(ptr);
	print_memory();
	write(1, "\n", 1);
}

void	test_zones_limits() {
	{
		size_t max_ptrs = TINY_ZONE_SIZE / TINY_MAX_BYTES;
		void *ptr[max_ptrs];
		for (size_t n = 0; n < max_ptrs; n++) {
			ptr[n] = malloc(TINY_MAX_BYTES);
		}
		void *last_ptr = malloc(TINY_MAX_BYTES - 8);

		print_memory(); // checker si la zone est bien full
		ft_putaddress((unsigned long)malloc(8), 1); // doit print (nil) car plus de place
		ft_putstr("\n");
		ft_putaddress((unsigned long)last_ptr, 1);
		ft_putstr(":");
		ft_putaddress((unsigned long)realloc(last_ptr, TINY_MAX_BYTES), 1); // zone complete, doit montrer deux fois la meme addresse
		ft_putstr("\n");
		last_ptr = realloc(last_ptr, 8); // doit reussir
		print_memory();

		free(last_ptr);
		for (size_t n = 0; n < max_ptrs; n++) {
			free(ptr[n]);
		}
		print_memory();
		write(1, "\n", 1);
	}
	{
		size_t max_ptrs = MED_ZONE_SIZE / MED_MAX_BYTES - 3;
		void *ptr[max_ptrs];
		for (size_t n = 0; n < max_ptrs - 1; n++) {
			ptr[n] = malloc(MED_MAX_BYTES);
		}
		ptr[max_ptrs - 1] = malloc(1024);
		void *last_ptr = malloc(1048);

		print_memory();
		ft_putaddress((unsigned long)malloc(TINY_MAX_BYTES + 8), 1);
		ft_putstr("\n");
		ft_putaddress((unsigned long)last_ptr, 1);
		ft_putstr(":");
		ft_putaddress((unsigned long)realloc(last_ptr, MED_MAX_BYTES), 1);
		ft_putstr("\n");
		last_ptr = realloc(last_ptr, TINY_MAX_BYTES + 8);
		print_memory();
		
		free(last_ptr);
		for (size_t n = 0; n < max_ptrs; n++) {
			free(ptr[n]);
		}
		print_memory();
		write(1, "\n", 1);
	}
}

void	test_free_null_nalloc() {
	void *ptr;
	free(ptr);
	free(NULL);

	void *p1 = malloc(8);
	void *p2 = malloc(TINY_MAX_BYTES + 8);
	void *p3 = malloc(MED_MAX_BYTES + 8);
	free(ptr);
	free(NULL);

	print_memory();
	free(p1);
	free(p1);
	free(p2);
	free(p2);
	free(p3);
	free(p3);
	print_memory();
	write(1, "\n", 1);
}

void	test_realloc_null_nalloc() {
	void *ptr;
	ft_putaddress((unsigned long)ptr, 1);
	ft_putstr(":");

	ptr = realloc(ptr, 8);
	ft_putaddress((unsigned long)ptr, 1);
	ft_putstr("\n");
	ft_putaddress((unsigned long)realloc(NULL, 8), 1);
	ft_putstr("\n");
	print_memory();

	free(ptr);
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
		ft_putstr(" bytes (STRUCT_ZONE)\n");

		curr = zo[0]->blocks;
		while (curr) {
			ft_putaddress((unsigned long)((char *)curr), 1);
			ft_putstr(" - ");
			ft_putaddress((unsigned long)((char *)curr + sizeof(t_block) - 1), 1);
			ft_putstr(" : ");
			ft_putsize(sizeof(t_block));
			ft_putstr(" bytes (STRUCT_BLOCK)\n");
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
		ft_putstr(" bytes (STRUCT_ZONE)\n");

		curr = zo[1]->blocks;
		while (curr) {
			ft_putaddress((unsigned long)((char *)curr), 1);
			ft_putstr(" - ");
			ft_putaddress((unsigned long)((char *)curr + sizeof(t_block) - 1), 1);
			ft_putstr(" : ");
			ft_putsize(sizeof(t_block));
			ft_putstr(" bytes (STRUCT_BLOCK)\n");
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
			ft_putstr(" bytes (STRUCT_ZONE)\n");
			ft_putaddress((unsigned long)((char *)curr2->blocks), 1);
			ft_putstr(" - ");
			ft_putaddress((unsigned long)((char *)curr2->blocks + sizeof(t_block) - 1), 1);
			ft_putstr(" : ");
			ft_putsize(sizeof(t_block));
			ft_putstr(" bytes (STRUCT_BLOCK)\n");
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
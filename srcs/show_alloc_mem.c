#include "malloc.h"

static void	ft_putstr(char *s) {
	int	i = -1;
	while (s[++i])
		write(1, &s[i], 1);
}

static void	ft_putsize(size_t size) {
	if (size > 9)
		ft_putsize(size / 10);
	char c = size % 10 + '0';
	write(1, &c, 1);
}

static void	ft_putaddress(unsigned long address, int first) {
	if (first)
		ft_putstr("0x");
	if (address > 15)
		ft_putaddress(address / 16, 0);
		char c = "0123456789abcdef"[address % 16];
	write(1, &c, 1);
}

int	is_zone_empty(t_zone *zone) {
	if (!zone)
		return 1;
	
	if (zo[2] && zone == zo[2]) {
		if (!zone->next && (!zone->blocks || zone->blocks->free))
			return 1;
	}
	else {
		if (!zone->blocks)
			return 1;
		if (zone->blocks && zone->blocks->free && !zone->blocks->next)
			return 1;
	}
	return 0;
}

void	show_alloc_mem() {
	t_block *curr;
	t_zone *curr2;

	if (is_zone_empty(zo[0]) && is_zone_empty(zo[1]) && is_zone_empty(zo[2])) {
		ft_putstr("No memory allocated.\n");
		return ;
	}

	curr = NULL;
	if (!is_zone_empty(zo[0])) {//!is_zone_empty(zo[0])) {
		ft_putstr("TINY : ");
		ft_putaddress((unsigned long)zo[0], 1);

		ft_putstr(" ( size = ");
		ft_putsize(zo[0]->size);
		ft_putstr(" bytes, size block = ");
		ft_putsize(zo[0]->size - sizeof(t_zone) - sizeof(t_block));
		ft_putstr(" bytes)");

		ft_putstr("\n");
		curr = zo[0]->blocks;
		while (curr) {
			if (!curr->free) {
				ft_putaddress((unsigned long)(curr + 1), 1);
				ft_putstr(" - ");
				ft_putaddress((unsigned long)(curr + curr->size), 1);
				ft_putstr(" : ");
				ft_putsize(curr->size);
				ft_putstr(" bytes\n");
			} else { // temporary, shows free blocks
				ft_putaddress((unsigned long)(curr + 1), 1);
				ft_putstr(" - ");
				ft_putaddress((unsigned long)(curr + curr->size), 1);
				ft_putstr(" : ");
				ft_putsize(curr->size);
				ft_putstr(" bytes (FREE BLOCK)\n");
			}
			curr = curr->next;
		}
	}

	curr = NULL;
	if (!is_zone_empty(zo[1])) {
		ft_putstr("MEDIUM : ");
		ft_putaddress((unsigned long)zo[1], 1);

		ft_putstr(" ( size = ");
		ft_putsize(zo[1]->size);
		ft_putstr(" bytes, size block = ");
		ft_putsize(zo[1]->size - sizeof(t_zone) - sizeof(t_block));
		ft_putstr(" bytes)");

		ft_putstr("\n");
		curr = zo[1]->blocks;
		while (curr) {
			if (!curr->free) {
				ft_putaddress((unsigned long)(curr + 1), 1);
				ft_putstr(" - ");
				ft_putaddress((unsigned long)(curr + curr->size), 1);
				ft_putstr(" : ");
				ft_putsize(curr->size);
				ft_putstr(" bytes\n");
			} else { // temporary, shows free blocks
				ft_putaddress((unsigned long)(curr + 1), 1);
				ft_putstr(" - ");
				ft_putaddress((unsigned long)(curr + curr->size), 1);
				ft_putstr(" : ");
				ft_putsize(curr->size);
				ft_putstr(" bytes (FREE BLOCK)\n");
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
			if (!curr2->blocks->free) {
				ft_putaddress((unsigned long)(curr2 + 1), 1);
				ft_putstr(" - ");
				ft_putaddress((unsigned long)(curr2 + curr2->size), 1);
				ft_putstr(" : ");
				ft_putsize(curr2->size);
				ft_putstr(" bytes\n");
			}
			curr2 = curr2->next;
		}
	}
}
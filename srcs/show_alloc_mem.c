#include "malloc.h"

void	ft_putstr(char *s) {
	int	i = -1;
	while (s[++i])
		write(0, &s[i], 1);
}

void	ft_putsize(size_t size) {
	if (size > 9)
		ft_putsize(size / 10);
	char c = size % 10 + '0';
	write(0, &c, 1);
}

void	ft_putaddress(unsigned long address, int first) {
	if (first)
		ft_putstr("0x");
	if (address > 15)
		ft_putaddress(address / 16, 0);
		char c = "0123456789abcdef"[address % 16];
	write(0, &c, 1);
}

void	show_alloc_mem() {
	t_block *curr;
	t_zone *curr2;

	if (!z_tiny && !z_med && !z_big) {
		ft_putstr("No memory allocated.\n");
		return ;
	}

	curr = NULL;
	if (z_tiny) {
		ft_putstr("TINY : ");
		ft_putaddress((unsigned long)z_tiny, 1);
		ft_putstr("\n");
		curr = z_tiny->blocks;
		while (curr) {
			if (!curr->free) {
				ft_putaddress((unsigned long)curr, 1);
				ft_putstr(" - ");
				ft_putaddress((unsigned long)(curr + curr->size), 1);
				ft_putstr(" : ");
				ft_putsize(curr->size);
				ft_putstr(" bytes\n");
			}
			curr = curr->next;
		}
	}

	curr = NULL;
	if (z_med) {
		ft_putstr("MEDIUM : ");
		ft_putaddress((unsigned long)z_med, 1);
		ft_putstr("\n");
		curr = z_med->blocks;
		while (curr) {
			if (!curr->free) {
				ft_putaddress((unsigned long)curr, 1);
				ft_putstr(" - ");
				ft_putaddress((unsigned long)(curr + curr->size), 1);
				ft_putstr(" : ");
				ft_putsize(curr->size);
				ft_putstr(" bytes\n");
			}
			curr = curr->next;
		}
	}

	curr2 = NULL;
	if (z_big) {
		ft_putstr("LARGE : ");
		ft_putaddress((unsigned long)z_big, 1);
		ft_putstr("\n");
		curr2 = z_big;
		while (curr2) {
			ft_putaddress((unsigned long)curr2, 1);
			ft_putstr(" - ");
			ft_putaddress((unsigned long)(curr2 + curr2->size), 1);
			ft_putstr(" : ");
			ft_putsize(curr2->size);
			ft_putstr(" bytes\n");
			curr2 = curr2->next;
		}
	}
}
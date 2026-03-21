#include "srcs/malloc.h"

#include <string.h>

int main(void) {
	printf("%d\n", TINY_MAX_BYTES);
	printf("%d\n", TINY_ZONE_SIZE);
	printf("%d\n", MED_MAX_BYTES);
	printf("%d\n\n", MED_ZONE_SIZE);

	/*ft_malloc(0);
	ft_malloc(1);
	ft_malloc(9);
	ft_malloc(17);
	ft_malloc(TINY_MAX_BYTES + 1);
	ft_malloc(TINY_MAX_BYTES + 9);
	ft_malloc(TINY_MAX_BYTES + 17);
	ft_malloc(MED_MAX_BYTES + 1);
	ft_malloc(MED_MAX_BYTES + 9);
	ft_malloc(MED_MAX_BYTES + 17);*/
	char *a = ft_malloc(1);
	char *large1 = ft_malloc(10000);
	show_alloc_mem();
	ft_free(a);
	ft_free(large1);
	show_alloc_mem();
	return 0;
}
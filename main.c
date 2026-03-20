#include "srcs/malloc.h"

#include <string.h>

int main(void) {
	printf("%d\n", TINY_MAX_BYTES);
	printf("%d\n", TINY_ZONE_SIZE);
	printf("%d\n", MED_MAX_BYTES);
	printf("%d\n\n", MED_ZONE_SIZE);

	ft_malloc(0);
	ft_malloc(TINY_MAX_BYTES + 1);
	ft_malloc(MED_MAX_BYTES + 1);
	//ft_free(s);

	show_alloc_mem();
	return 0;
}
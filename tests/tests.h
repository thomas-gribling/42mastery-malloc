#include "../srcs/malloc.h"

void	show_alloc_mem_debug();

int		test_hundred_malloc();
void	test_speed_thousand_malloc();
	
void	test_double();
void	test_triple();
	
void	test_realloc_basic();
void	test_realloc_smaller();
void	test_realloc_bigger();

void	test_failing_cases();
void	test_zones_limits();
void	test_free_null_nalloc();
void	test_realloc_null_nalloc();
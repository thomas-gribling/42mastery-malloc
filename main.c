#include "tests/tests.h"

int main(void) {

	// Teste la possibilite de malloc 100 fois par zone
	ft_putstr("=== 100 MALLOCS TEST ===\n");
	if (test_hundred_malloc())
		return 1;

	// Test de vitesse
	ft_putstr("=== 1000 MALLOCS SPEEDTEST ===\n");
	test_speed_thousand_malloc();
	
	// Test de la fonction malloc + free
	ft_putstr("=== MALLOC TESTS ===\n");
	test_double();
	test_triple();
	
	// Test de la fonction realloc + free
	ft_putstr("=== REALLOC TESTS ===\n");
	test_realloc_basic();
	test_realloc_smaller();
	test_realloc_bigger();

	// Test de failing cases
	ft_putstr("=== FAIL CASES MALLOC/REALLOC ===\n");
	test_failing_cases();

	// Limites de zones malloc et realloc
	ft_putstr("=== ZONE LIMITS ===\n");
	test_zones_limits();
	
	// Pointeurs NULL, non alloues et doubles free
	ft_putstr("=== FREE NULL AND NON-ALLOC ===\n");
	test_free_null_nalloc();
	
	// Realloc sur NULL et non alloues
	ft_putstr("=== REALLOC NULL AND NON-ALLOC ===\n");
	test_realloc_null_nalloc();

	return 0;
}
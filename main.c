#include "tests/tests.h"

int main(void) {

	// Teste la possibilite de malloc 100 fois par zone
	printf("=== 100 MALLOCS TEST ===\n");
	if (test_hundred_malloc())
		return 1;

	// Test de vitesse
	printf("=== 1000 MALLOCS SPEEDTEST ===\n");
	test_speed_thousand_malloc();
	
	// Test de la fonction malloc + free
	printf("=== MALLOC TESTS ===\n");
	test_double();
	test_triple();
	
	// Test de la fonction realloc + free
	printf("=== REALLOC TESTS ===\n");
	test_realloc_basic();
	test_realloc_smaller();
	test_realloc_bigger();

	// Test de failing cases
	printf("=== FAIL CASES MALLOC/REALLOC ===\n");
	test_failing_cases();

	// Limites de zones malloc et realloc
	printf("=== ZONE LIMITS ===\n");
	test_zones_limits();
	
	// Pointeurs NULL, non alloues et doubles free
	printf("=== FREE NULL AND NON-ALLOC ===\n");
	test_free_null_nalloc();
	
	// Realloc sur NULL et non alloues
	printf("=== REALLOC NULL AND NON-ALLOC ===\n");
	test_realloc_null_nalloc();

	return 0;
}
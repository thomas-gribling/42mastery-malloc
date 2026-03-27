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

	return 0;
}
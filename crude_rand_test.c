#include <stdio.h>
#include <stdlib.h>

#include "version.h"

#include "iso_c_sample_rand.h"
#include "netbsd_rand.h"

#define COUNT 64

enum behavior { normal, deterministic };

static void analyze(char *name, int (*rand_func)(void), enum behavior behavior) {
    printf("Testing the low-order bits of the result of rand() from %s\n", name);
    int alternating = 1;
    int ones = 0;
    int previous;
    int i;

    if (behavior == deterministic) {
#ifdef __OpenBSD__
	srand_deterministic(1);
#else
	fprintf(stdout, "%s:%d: Internal error\n", __FILE__, __LINE__);
	return;
#endif
    }

    for (i = 0; i < COUNT; i ++) {
        const int low_order_bit = rand_func() & 1;
        printf("%d", low_order_bit);
        if (low_order_bit == 1) {
            ones ++;
        }
        if (i > 0 && low_order_bit == previous) {
            alternating = 0;
        }
        previous = low_order_bit;
    }
    putchar('\n');

    if (alternating) {
        puts("Low order bits alternate 0 and 1 (bad)");
    }
    else {
        printf("%d samples, %d zeros, %d ones\n",
               COUNT, COUNT-ones, ones);
    }
}

static void test_determinism(void) {
    int x1, x2, x3;
    int y1, y2, y3;
    srand(1);
    x1 = rand(); x2 = rand(); x3 = rand();
    srand(1);
    y1 = rand(); y2 = rand(); y3 = rand();
    if (x1 == y1 && x2 == y2 && x3 == y3) {
        puts("The current implementation's rand() is properly deterministic");
    }
    else {
        puts("The current implementation's rand() is not deterministic (non-conforming)");
    }
}

int main(void) {
    printf("crude_rand_test %s\n", VERSION);
    putchar('\n');

    analyze("current implementation", rand, normal);
    putchar('\n');

#ifdef __OpenBSD__
    analyze("current implementation with srand_deterministic(1)", rand, deterministic);
    putchar('\n');
#endif

    analyze("ISO C sample implementation", iso_c_sample_rand, normal);
    putchar('\n');

    analyze("NetBSD", netbsd_rand, normal);
    putchar('\n');

    test_determinism();

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#include "iso_c_sample_rand.h"
#include "netbsd_rand.h"

#define COUNT 64

static void analyze(char *name, int (*rand_func)(void)) {
    printf("Testing the low-order bits of the result of rand() from %s\n", name);
    int alternating = 1;
    int ones = 0;
    int previous;
    int i;

    for (i = 0; i < COUNT; i ++) {
        const int low_order_bit = rand() & 1;
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

int main(void) {
    analyze("current implementation", rand);
    putchar('\n');

    analyze("ISO C sample implementation", iso_c_sample_rand);
    putchar('\n');

    analyze("NetBSD", netbsd_rand);
    return 0;
}

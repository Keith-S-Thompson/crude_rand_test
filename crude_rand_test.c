#include <stdio.h>
#include <stdlib.h>

#define COUNT 64

void analyze(int *low_order_bits) {
    int i;
    int alternating = 1;
    int ones = 0;
    for (i = 0; i < COUNT; i ++) {
        printf("%d", low_order_bits[i]);
        if (low_order_bits[i] == 1) {
            ones ++;
        }
        if (i > 0 && low_order_bits[i] == low_order_bits[i-1]) {
            alternating = 0;
        }
    }
    putchar('\n');
    if (alternating) {
        puts("Low order bits alternate 0 and 1 (bad)");
    }
    else {
        printf("%d zeros, %d ones out of %d total samples\n",
               COUNT-ones, ones, COUNT);
    }
}

int main(void) {
    int low_order_bits[COUNT];
    int i;

    puts("Testing the low-order bit of the result of rand() ...");
    for (i = 0; i < COUNT; i ++) {
        low_order_bits[i] = rand() & 1;
    }
    analyze(low_order_bits);
    return 0;
}

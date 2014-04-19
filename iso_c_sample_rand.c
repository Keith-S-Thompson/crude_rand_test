#include "iso_c_sample_rand.h"

/*
 * Sample implementation copied from the ISO C standard,
 * N1570 draft, section 7.22.2.2 paragraph 5.
 *
 * (The sample implementation is non-normative; conforming C
 * implementations are not required to use it.)
 */

static unsigned long int next = 1;

int iso_c_sample_rand(void) // RAND_MAX assumed to be 32767
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % 32768;
}

void iso_c_sample_srand(unsigned int seed)
{
    next = seed;
}

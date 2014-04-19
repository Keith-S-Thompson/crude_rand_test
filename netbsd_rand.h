#ifndef NETBSD_RAND_H
#define NETBSD_RAND_H

#define netbsd_RAND_MAX 0x7fffffff

int netbsd_rand(void);
void netbsd_srand(unsigned int seed);

#endif

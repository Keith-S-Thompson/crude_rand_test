crude_rand_test
===============

Crude test for crude rand() implementations

TL;DR: Test whether the low-order bit of the value returned by C's
`rand()` function consistently alternates between 0 and 1.

### NOTE:

A previous version of this program had a serious bug; it didn't
actually call rand() implementations other than the one provided by
the current system.  The current version displays the date when it
was last updated; results from versions prior to that are invalid
(other than the output for the current implementation).

---

ISO C specifies two functions for generating pseudo-random numbers,
declared in `<stdlib.h>`:

    void srand(unsigned int seed);

    int rand(void);

You can read the description in any decent C reference, or in the
standard itself, so I won't repeat it here.

The common wisdom is that `rand()` is not suitable for use in
cryptography. For one thing, the seed is an `unsigned int`, which
means that if `unsigned int` is 32 bits, there are only 2<sup>32</sup>
possible sequences (and possibly only 2<sup>32</sup> possible internal
states).  If your system's security depends on random numbers, *don't
use `rand()`.

Even worse, there are some implementations where the low-order bit
of the value returned by `rand()` is almost completely useless; it
alternates between 0 and 1.  More generally, the Nth low-order bit
repeats in cycle of 2<sup>N>, so for example the low-order 8 bits
will be exactly the same on every 8th call.

The excellent [comp.lang.c FAQ](http://www.c-faq.com/) mentions this
in question 13.18:

> Poor pseudorandom number generators (such as the ones unfortunately
> supplied with some systems) are not very random in the low-order
> bits. (In fact, for a pure linear congruential random number generator
> with period 2**e, and this tends to be how random number generators
> for e-bit machines are written, the low-order n bits repeat with period
> 2**n.) For this reason, it's preferable to use the higher-order bits:
> see question [13.16](http://www.c-faq.com/lib/randrange.html).
> 
> References: Knuth Sec. 3.2.1.1 pp. 12-14 

In a recent discussion on the comp.lang.c newsgroup (visible
[here](https://groups.google.com/forum/#!msg/comp.lang.c/nkNqr39n4xY/aN2MnvrbAv4J)
via the inexcusably clumsy Google Groups interface), I expressed
skepticism that this was still an issue.  After all, the sample
implementation in the ISO C standard (first published in 1989) doesn't
have this particular problem.  I posted a small test program to test
for the problem.

Ike Naar wrote that running my test program on NetBSD nb2 20110806
shows that the low-order bit *does* alternate between 0 and 1, and
Udyant Wig posted the source code for the implementation of `rand()`
in NetBSD's libc.

This small project is a C program that tests an implementation's
`rand()` function for this particular issue.  It doesn't perform any
other tests of the quality, just whether the low-order bit consistenly
alternates between 0 and 1.  The program deliberately does not call
`srand()` (which is equivalent to calling `srand()` with an initial
seed of 1).

The current version tests the current implementation's
`rand()` function as well as a couple of others, compiled
from source.  (TODO: Add the FreeBSD version, source code
[here](http://www.opensource.apple.com/source/Libc/Libc-997.1.1/stdlib/FreeBSD/rand.c).

If anyone would care to run this on their system, *particularly* if
it's a reasonably modern system that exhibits the problem, please
send me the results and I'll publish them here (when and if I get
around to it).

    -- Keith Thompson <Keith.S.Thompson@gmail.com> Sat 2014-04-19

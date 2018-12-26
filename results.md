Results
=======

Linux Mint 14, GNU libc6 2.15

    Testing the low-order bit of the result of rand() ...
    1011110011010110000010110001111000111010111101001010100100011101
    30 zeros, 34 ones out of 64 total samples

---

Ubuntu 18.04.1 LTS (bionic), GNU libc6 2.27-3ubuntu1

    crude_rand_test, last updated Mon 2014-04-21 15:49:58 UTC

    Testing the low-order bits of the result of rand() from current implementation
    1011110011010110000010110001111000111010111101001010100100011101
    64 samples, 30 zeros, 34 ones

    Testing the low-order bits of the result of rand() from ISO C sample implementation
    0011110100110011111000111011000100110110001110110010010001111110
    64 samples, 29 zeros, 35 ones

    Testing the low-order bits of the result of rand() from NetBSD
    0101010101010101010101010101010101010101010101010101010101010101
    Low order bits alternate 0 and 1 (bad)

---

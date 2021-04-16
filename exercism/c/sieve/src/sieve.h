#ifndef SIEVE_H
#define SIEVE_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <math.h>

/// Calculate at most `max_primes` prime numbers in the interval [2,limit] 
/// using the Sieve of Eratosthenes and store the prime numbers in `primes`
/// in increasing order.
/// The function returns the number of calculate primes.
uint32_t sieve(uint32_t limit, uint32_t * primes, size_t max_primes);
bool is_primary(int value);

#endif

#include "sieve.h"

uint32_t sieve(uint32_t limit, uint32_t * primes, size_t max_primes) {
    int count = 0;
    if (limit == 1) {
        return (uint32_t)count;
    }
    for (int i = 2; i <= (int)limit; i++) {
        if (count < (int)max_primes && is_primary(i)) {
            primes[count++] = (uint32_t)i;
        }
    }
    return (uint32_t)count;
}

bool is_primary(int value) {
  for(int i = 2; i < value ; ++i) {
    if(value % i == 0 ) {
        return false;
    }
  }
  return true;
}

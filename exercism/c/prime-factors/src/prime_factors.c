#include "prime_factors.h"

size_t find_factors(uint64_t n, uint64_t factors[static MAXFACTORS]) {
    int counts = 0;

    for(uint64_t i = 2; i <= n; i++) {
        if (n % i == 0) {
            n /= i;
            factors[counts++] = i;
            i = 1;
        }
    }
    return counts;
}

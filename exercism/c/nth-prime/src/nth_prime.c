#include "nth_prime.h"

uint32_t nth(uint32_t n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 2;
    }

    int i, j, k;
    int counts = 1;
	for (i = 3; i <= 10000000; i += 2) {
		k = 0;
		for (j = 3 ; j <= sqrt(i); j += 2) {
			if (i % j == 0) {
				k = 1;
				break;
			}
		}

		if (k == 0) {
            counts++;
        }
        if (counts == (int)n) {
            return i;
        }
	}
    return -1;
}

#include "pythagorean_triplet.h"

triplets_t *triplets_with_sum(uint16_t sum) {
    triplets_t *triplets;
    triplets = malloc(sizeof(triplets_t));
    triplets->count = 0;
    triplets->triplets = malloc(sizeof(triplets) * 1024);
    for (int a = 0; a < (int)sum; a++) {
        for (int b = a + 1; b < (int)sum; b++) {
            int c = sum - a - b;
            if (b >= c) {
                continue;
            }
            if (pow(a, 2) + pow(b, 2) == pow(c, 2)) {
                triplets->triplets[triplets->count++] = (triplet_t){.a=a, .b=b, .c=c};
            }
        }
    }
    return triplets;
}

void free_triplets(triplets_t *triplets) {
    free(triplets->triplets);
    free(triplets);
}

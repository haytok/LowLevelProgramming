#ifndef PYTHAGOREAN_TRIPLET
#define PYTHAGOREAN_TRIPLET

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <math.h>

#define LENGTH 3

typedef struct triplet_t triplet_t;
typedef struct triplets_t triplets_t;

struct triplet_t {
    int a;
    int b;
    int c;
};

struct triplets_t {
    int count;
    triplet_t *triplets;
};

triplets_t *triplets_with_sum(uint16_t sum);
void free_triplets(triplets_t *triplets);

#endif

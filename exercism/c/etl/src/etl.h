#ifndef ETL_H
#define ETL_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

typedef struct {
   int score;
   const char *letters;
} legacy_map;

typedef struct {
   char key;
   int value;
} new_map;

int convert(const legacy_map * input, const size_t input_len,
            new_map ** output);
int compare(const void *a, const void *b);

#endif

#ifndef ALL_YOUR_BASE_H
#define ALL_YOUR_BASE_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <math.h>

#define DIGITS_ARRAY_SIZE 64

size_t rebase(
    int8_t digits[DIGITS_ARRAY_SIZE],
    int16_t input_base,
    int16_t output_base,
    size_t input_length
);

#endif

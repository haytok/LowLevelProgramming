#ifndef RATIONAL_NUMBERS
#define RATIONAL_NUMBERS

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <math.h>

typedef struct {
    int numerator;
    int denominator;
} rational_t;

rational_t mixin_of_add_and_subtract(rational_t r1, rational_t r2, char *type);
rational_t add(rational_t r1, rational_t r2);
rational_t subtract(rational_t r1, rational_t r2);
rational_t mixin_of_multiply_and_divide(rational_t r1, rational_t r2, char *type);
rational_t multiply(rational_t r1, rational_t r2);
rational_t divide(rational_t r1, rational_t r2);
int my_abs(int value);
rational_t absolute(rational_t r);
double my_pow(double value, int n);
rational_t exp_rational(rational_t r, uint16_t n);
int my_root(double value, int n);
float exp_real(uint16_t x, rational_t r);
rational_t reduce(rational_t r);
int get_gcm(int x, int y);
int get_lcm(int a, int b);

#endif

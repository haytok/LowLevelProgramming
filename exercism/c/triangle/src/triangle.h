#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>

typedef struct {
   double a;
   double b;
   double c;
} triangle_t;

bool is_equilateral(triangle_t sides);
bool is_isosceles(triangle_t sides);
bool is_scalene(triangle_t sides);
bool is_triangle(double x, double y);
bool is_exist(triangle_t sides);
bool is_triple(double x, double y, double z);

#endif

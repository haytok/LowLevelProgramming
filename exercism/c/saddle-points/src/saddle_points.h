#ifndef SADDLE_POINTS_H
#define SADDLE_POINTS_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>

typedef struct saddle_point_t saddle_point_t;
typedef struct saddle_points_t saddle_points_t;

struct saddle_point_t {
    int row;
    int column;
};

struct saddle_points_t {
    int count;
    saddle_point_t *points;
};

saddle_points_t *saddle_points(int row, int column, uint8_t matrix[row][column]);
void free_saddle_points(saddle_points_t *actual);
int get_max_value(int value, int base);
int get_min_value(int value, int base);

#endif

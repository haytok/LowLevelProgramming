#include "saddle_points.h"

saddle_points_t *saddle_points(int row, int column, uint8_t matrix[row][column]) {
    int *row_max = malloc(sizeof(int) * row);
    for (int i = 0; i < row; i++) {
        row_max[i] = 0;
    }
    int *column_min = malloc(sizeof(int) * column);
    for (int i = 0; i < column; i++) {
        column_min[i] = 1000000;
    }
    for (int row_index = 0; row_index < row; row_index++) {
        for (int column_index = 0; column_index < column; column_index++) {
            int value = matrix[row_index][column_index];
            row_max[row_index] = get_max_value(row_max[row_index], value);
            column_min[column_index] = get_min_value(column_min[column_index], value);
        }
    }
    saddle_points_t *actual;
    actual = malloc(sizeof(saddle_points_t));
    actual->count = 0;
    actual->points = malloc(sizeof(saddle_point_t *) * 1024);
    for (int row_index = 0; row_index < row; row_index++) {
        for (int column_index = 0; column_index < column; column_index++) {
            if (row_max[row_index] == column_min[column_index]) {
                saddle_point_t point = (saddle_point_t){
                    .row = row_index + 1,
                    .column = column_index + 1,
                };
                actual->points[actual->count++] = point;
            }
        }
    }
    return actual;
}

void free_saddle_points(saddle_points_t *actual) {
    free(actual->points);
    free(actual);
}

int get_max_value(int value, int base) {
    return value > base ? value : base;
}

int get_min_value(int value, int base) {
    return value < base ? value : base;
}

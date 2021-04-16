#include "pascals_triangle.h"

uint8_t **create_triangle(size_t rows) {
    uint8_t **triangle;
    if (rows == 0) {
        triangle = malloc(sizeof(uint8_t *) * 1);
        triangle[0] = malloc(sizeof(uint8_t) * 1);;
        return triangle;
    } else {
        // 二次元配列の初期化
        triangle = malloc(sizeof(uint8_t *) * (int)rows);
        for (size_t i = 0; i < rows; i++) {
            triangle[i] = malloc(sizeof(uint8_t) * (int)rows);
            for (size_t j = 0; j < rows; j++) {
                if (j == 0 || i == j) {
                    triangle[i][j] = 1;
                } else {
                    if (i > 1 && i < rows) {
                        triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j];
                    }
                }
            }
        }
        // Debug
        // for (size_t i = 0; i < rows; i++) {
        //     for (size_t j = 0; j <= i; j++) {
        //         printf("%d\n", triangle[i][j]);
        //     }
        // }
        return triangle;
    }
}

void free_triangle(uint8_t ** triangle, size_t rows) {
    for (int i = 0; i < (int)rows; i++) {
        free(triangle[i]);
    }
    free(triangle);
}

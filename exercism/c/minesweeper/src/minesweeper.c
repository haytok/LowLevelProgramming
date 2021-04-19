#include "minesweeper.h"

#define LENGTH 32
#define MOVE_LENGTH 8

char **annotate(const char **minefield, const size_t rows) {
    char **ans;
    ans = malloc(sizeof(char *) * (int)rows);
    if (rows == 0) {
        ans[0] = NULL;
        return NULL;
    }
    int asterisk_counts = 0;
    int asterisk_rows[LENGTH] = {0};
    int asterisk_columns[LENGTH] = {0};
    int columns = 0;
    int row = 0;
    int column = 0;
    for (row = 0; row < (int)rows; row++) {
        columns = strlen(minefield[row]);
        for (column = 0; column < (int)columns; column++) {
            if (minefield[row][column] == '*') {
                asterisk_rows[asterisk_counts] = row;
                asterisk_columns[asterisk_counts] = column;
                asterisk_counts++;
            }
        }
    }
    if (asterisk_counts == 0 || rows * columns == asterisk_counts) {
        return minefield;
    }
    move_v move_array[MOVE_LENGTH] = {
        {-1, -1},
        {-1, 0},
        {-1, 1},
        {0, 1},
        {1, 1},
        {1, 0},
        {1, -1},
        {0, -1},
    };
    for (row = 0; row < (int)rows; row++) {
        // この処理は必須
        ans[row] = malloc(sizeof(char *) * columns);
        for (column = 0; column < (int)columns; column++) {
            int counts = 0;
            for (int i = 0; i < MOVE_LENGTH; i++) {
                int n_row = row + move_array[i].row;
                int n_column = column + move_array[i].column;
                if (
                    n_row >= 0
                    && n_row < (int)rows
                    && n_column >= 0
                    && n_column < (int)columns
                ) {
                    if (is_exist(n_row, n_column, asterisk_rows, asterisk_columns, asterisk_counts)) {
                        counts++;
                    }
                }
            }
            if (minefield[row][column] == '*') {
                ans[row][column] = '*';
            } else {
                ans[row][column] = counts > 0 ? '0' + counts : ' ';
            }
        }
    }
    return ans;
}

void free_annotation(char **annotation) {}

bool is_exist(int n_row, int n_column, int asterisk_rows[LENGTH], int asterisk_columns[LENGTH], int asterisk_counts) {
    for (int i = 0; i < asterisk_counts; i++) {
        if (asterisk_rows[i] == n_row && asterisk_columns[i] == n_column ) {
            return true;
        }
    }
    return false;
}

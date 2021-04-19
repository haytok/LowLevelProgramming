#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#define LENGTH 32
#define MOVE_LENGTH 8

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>

typedef struct move_v move_v;

struct move_v {
    int row;
    int column;
};

char **annotate(const char **minefield, const size_t rows);
void free_annotation(char **annotation);
bool is_exist(int n_row, int n_column, int asterisk_rows[LENGTH], int asterisk_columns[LENGTH], int asterisk_counts);
bool is_neighbor(int n_row, int n_column, move_v asterisk_position[LENGTH], int asterisk_counts);

#endif

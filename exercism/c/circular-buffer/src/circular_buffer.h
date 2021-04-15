#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>

// このデータ構造を返る発想が飛んでた ...
// typedef int buffer_value_t;
typedef int buffer_value_t;
typedef struct circular_buffer_t circular_buffer_t;

struct circular_buffer_t {
    int read_index;
    int write_index;
    int capacity;
    buffer_value_t *buffer;
};

circular_buffer_t *new_circular_buffer(size_t capacity);
int16_t write(circular_buffer_t *buffer, buffer_value_t value);
int16_t overwrite(circular_buffer_t *buffer, buffer_value_t value);
int16_t read(circular_buffer_t *buffer, buffer_value_t *read_value);
void clear_buffer(circular_buffer_t *buffer);
void delete_buffer(circular_buffer_t *buffer);
int get_array_length(circular_buffer_t *buffer);

#endif

#include "circular_buffer.h"

circular_buffer_t *new_circular_buffer(size_t capacity) {
    circular_buffer_t *buffer = malloc(sizeof(circular_buffer_t));
    // buffer->capacity = capacity;
    // buffer->read_index = 0;
    // buffer->write_index = 0;
    // buffer->buffer = malloc(sizeof(buffer_value_t) * capacity);
    *buffer = (circular_buffer_t) {
        .read_index = 0,
        .write_index = 0,
        .capacity = capacity,
        .buffer = malloc(sizeof(buffer_value_t) * capacity)
    };
    return buffer;
}

int16_t read(circular_buffer_t *buffer, buffer_value_t *read_value) {
    if (buffer->read_index == buffer->write_index) {
        errno = ENODATA;
        return EXIT_FAILURE; // 1
    }
    read_value[0] = buffer->buffer[buffer->read_index++ % buffer->capacity];
    return EXIT_SUCCESS; // 0
}

void delete_buffer(circular_buffer_t *buffer) {
    free(buffer->buffer);
    free(buffer);
}

int16_t write(circular_buffer_t *buffer, buffer_value_t value) {
    if (get_array_length(buffer) == buffer->capacity) {
        errno = ENOBUFS;
        return EXIT_FAILURE;
    }
    buffer->buffer[buffer->write_index++ % buffer->capacity] = value;
    return EXIT_SUCCESS;
}

int16_t overwrite(circular_buffer_t *buffer, buffer_value_t value) {
    write(buffer, value);
    // write_index と read_index の差はリングバッファに書き込まれた値の数である。
    // この値と capacity の大きさが等しい時は、リングバッファがフルに埋まっている。
    if (errno == ENOBUFS) {
        buffer->buffer[buffer->write_index++ % buffer->capacity] = value;
        buffer->read_index++;
    }
    return EXIT_SUCCESS;
}

void clear_buffer(circular_buffer_t *buffer) {
    buffer->read_index = 0;
    buffer->write_index = 0;
}

int get_array_length(circular_buffer_t *buffer) {
    return buffer->write_index - buffer->read_index;
}

// 0 1 2 3 4
// <- read_index write_index ->

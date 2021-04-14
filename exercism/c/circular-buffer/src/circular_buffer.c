#include "circular_buffer.h"

// size_t length = 0;
circular_buffer_t *start;
// = malloc(sizeof(circular_buffer_t) * 1024);

circular_buffer_t *new_circular_buffer(size_t capacity) {
    circular_buffer_t *buffer = malloc(sizeof(circular_buffer_t) * capacity);
    // length = capacity;
    start = buffer;
    return buffer;
}

int16_t read(circular_buffer_t *buffer, buffer_value_t *read_value) {
    printf("read %d %d %d\n", *buffer, read_value[0], EXIT_FAILURE);
    if (*buffer == 0) {
        errno = ENODATA;
        return EXIT_FAILURE; // 1
    }
    // circular_buffer_t *head = buffer;
    // while (*head) {
    //     if (*head == read_value[0]) {
    //         printf("*head %d\n", *head);
    //         read_value[0] = *head;
    //         return EXIT_SUCCESS;  // 0
    //     }
    //     head++;
    // }
    read_value[0] = *buffer;
    *buffer = 0;
    if ((int)(buffer - start) == (get_array_length(buffer) - 1)) {
        buffer = start;
    } else {
        buffer++;
    }
    printf("diff %ld\n", (buffer - start));
    // if (*buffer == 0) {
    //     buffer = head;
    // }
    printf("Hello\n");
    return EXIT_SUCCESS; // 0
}

void delete_buffer(circular_buffer_t *buffer) {
    free(buffer);
}

int16_t write(circular_buffer_t *buffer, buffer_value_t value) {
    *buffer = value;
    printf(
        "In write, get_array_length %d %d %d\n",
        get_array_length(buffer),
        *buffer,
        (int)(buffer - start)
    );
    if ((int)(buffer - start) == (get_array_length(buffer) - 1)) {
        printf("Helssssl\n");
        buffer = start;
    } else {
        buffer++;
    }
    printf("diff %d\n", (int)(buffer - start));
    return EXIT_SUCCESS;
}

int16_t overwrite(circular_buffer_t *buffer, buffer_value_t value) {
    printf("%d %d\n", buffer[0], value);
    return 0;
}

void clear_buffer(circular_buffer_t *buffer) {
    printf("%d\n", buffer[0]);   
}

int get_array_length(int *array) {
    return sizeof(array) / sizeof(array[0]);
}

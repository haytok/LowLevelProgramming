#include <stdio.h>
#include <stdlib.h>

#define N_LINES 5
#define MAX_LINE_LENGTH 1024

static char ring_buffer[N_LINES][MAX_LINE_LENGTH];

void do_tail(FILE *file);

// cat tail.c | ./tail
int main(int argc, char **argv) {
    if (argc != 1)  {
        fprintf(stderr, "Usage: %s < infile\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    do_tail(stdin);
    exit(EXIT_SUCCESS);
}

void do_tail(FILE *file) {
    int current_index = 0;
    int read_lines = 0;
    while (fgets(ring_buffer[current_index], MAX_LINE_LENGTH, file)) {
        current_index++;
        if (current_index > N_LINES) {
            current_index = 0;
        }
        read_lines++;
    }

    // リングバッファが満タンになってないケースを想定
    if (read_lines < N_LINES) {
        for (int n = 0; n < current_index; n++) {
            printf("%s", ring_buffer[n]);
        }
    } else {
        for (int n = N_LINES; n > 0; n--) {
            current_index++;
            if (current_index > N_LINES) {
                current_index = 0;
            }
            printf("%s", ring_buffer[current_index]);
        }
    }
}

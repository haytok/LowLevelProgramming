#include <stdio.h>
#include <stdlib.h>

void do_head(FILE *file, int n);
void die(char *path);

// cat head.c > 
// ./head 5 file_name
int main(int argc, char **argv) {
    if (argc < 2) {
        die(argv[0]);
    } else {
        int n = atoi(argv[1]);
        if (argc == 2) {
            do_head(stdin, n);
        } else if (argc == 3) {
            char *path = argv[2];
            FILE *file = fopen(path, "r");
            if (!file) {
                die(path);
            }
            do_head(file, n);
        } else {
            printf("arguments are 3.");
        }
    }
    exit(EXIT_SUCCESS);
}

void do_head(FILE *file, int n) {
    int c;
    while (n != 0 && ((c = fgetc(file)) != EOF)) {
        if (putchar(c) < 0) {
            exit(EXIT_FAILURE);
        }
        if (c == '\n') {
            n--;
        }
    }
}

void die(char *path) {
    perror(path);
    exit(EXIT_FAILURE);
}

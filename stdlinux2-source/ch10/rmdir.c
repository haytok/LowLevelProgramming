#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void die(char *path);

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "%s: no arguments.\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < argc; i++) {
        char *dir_name = argv[i];
        if (rmdir(dir_name) < 0) {
            die(dir_name);
        }
    }
    exit(EXIT_SUCCESS);
}

void die(char *path) {
    perror(path);
    exit(EXIT_FAILURE);
}

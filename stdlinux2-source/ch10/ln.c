#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void die(char *path);

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "%s: wrong arguments.\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (symlink(argv[1], argv[2]) < 0) {
        die(argv[1]);
    }
    exit(EXIT_SUCCESS);
}

void die(char *path) {
    perror(path);
    exit(EXIT_FAILURE);
}

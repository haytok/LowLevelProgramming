#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void die(char *path);

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "no mode given.\n");
        exit(EXIT_FAILURE);
    }
    int mode = strtol(argv[1], NULL, 8);
    for (int i = 2; i < argc; i++) {
        if (chmod(argv[i], mode)) {
            die(argv[i]);
        }
    }
    exit(EXIT_SUCCESS);
}

void die(char *path) {
    perror(path);
    exit(EXIT_FAILURE);
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

void die(char *path);

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "%s: no arguments.\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < argc; i++) {
        char *dir_name = argv[i];
        if (mkdir(dir_name, 0777) < 0) {
            die(dir_name);
        }
    }
}

void die(char *path) {
    perror(path);
    exit(EXIT_FAILURE);
}

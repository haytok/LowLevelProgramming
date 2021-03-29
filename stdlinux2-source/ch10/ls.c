#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

void do_ls(char *path);
void die(char *path);

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "%s: no arguments.\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *path = argv[1];
    do_ls(path);
}

void do_ls(char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        die(path);
    }
    struct dirent *entry;
    while (entry = readdir(dir)) {
        printf("%s\n", entry->d_name);
    }
    if (closedir(dir) < 0) {
        die(path);
    }
}

void die(char *path) {
    perror(path);
    exit(EXIT_FAILURE);
}

#include <stdio.h>
#include <stdlib.h>

void do_cat(FILE *fd);
void die(char *string);

int main(int argc, char **argv) {
    if (argc < 2) {
        // 従来の方式と違って file descreptor を使用すると、do_cat 関数を改良しないといけない。
        do_cat(stdin);
    }

    for (int i = 1; i < argc; i++) {
        char *path = argv[i];
        FILE *fd = fopen(path, "r");
        if (!fd) {
            die(path);
        }
        do_cat(fd);
        if (fclose(fd) != 0) {
            die(path);
        }
    }

    exit(EXIT_SUCCESS);
}

void do_cat(FILE *fd) {
    int c;

    while ((c = fgetc(fd)) != EOF) {
        if (putchar(c) < 0) {
            exit(EXIT_FAILURE);
        }
    }
}

void die(char *string) {
    perror(string);
    exit(EXIT_FAILURE);
}

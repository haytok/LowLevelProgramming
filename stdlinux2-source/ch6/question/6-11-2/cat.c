#include <stdio.h>
#include <stdlib.h>

int do_wc_l(FILE *fd);
void die(char *string);

int main(int argc, char **argv) {
    if (argc < 2) {
        // 従来の方式と違って file descreptor を使用すると、do_cat 関数を改良しないといけない。
        printf("counts: %d\n", do_wc_l(stdin));
    }

    for (int i = 1; i < argc; i++) {
        char *path = argv[i];
        FILE *fd = fopen(path, "r");
        if (!fd) {
            die(path);
        }
        printf("counts: %d\n", do_wc_l(fd));
        if (fclose(fd) != 0) {
            die(path);
        }
    }

    exit(EXIT_SUCCESS);
}

int do_wc_l(FILE *fd) {
    int c;
    int count = 0; // 初期化しないと変な値で初期化されてしまう。
    int prev = '\n';

    while ((c = fgetc(fd)) != EOF) {
        switch (c) {
            case '\n': {
                if (fputs("$\n", stdout) < 0) {
                    exit(EXIT_FAILURE);
                }
                count += 1;
                break;
            }
            case '\t': {
                if (fputs("\\t", stdout)) {
                    exit(EXIT_FAILURE);
                }
                break;
            }
            default: {
                if (putchar(c) < 0) {
                    exit(EXIT_FAILURE);
                }
                break;
            }
        }
    }
    return count;
}

void die(char *string) {
    perror(string);
    exit(EXIT_FAILURE);
}

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 2048

void do_cat(char *path);
void die(char *string);

int main(int argc, char **argv) {
    if (argc < 2) {
        // 従来の方式と違って file descreptor を使用すると、do_cat 関数を改良しないといけない。
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        do_cat(argv[i]);
    }

    exit(EXIT_SUCCESS);
}

void do_cat(char *path) {
    FILE *fd = fopen(path, "r");
    if (!fd) {
        die(path);
    }

    char buf[BUFFER_SIZE];

    for (;;) {
        size_t n_fread = fread(buf, 1, sizeof(buf), fd);
        // p.120 を参考にする
        // 読み込みのエラーを検出
        if (ferror(fd) > 0) {
            die(path);
        }

        size_t n_fwrite = fwrite(buf, 1, n_fread, stdout);
        // 書き込んだバイト数が読み込んだバイト数より小さい時、書き込みきれてないのでエラーを吐く
        if (n_fwrite < n_fread) {
            die(path);
        }
        // size * nmemb バイト読む前に EOF に到達した場合には nmemb より小さい値が返る。
        if (n_fread < sizeof(buf)) {
            break;
        }
    }

    if (fclose(fd) != 0) {
        die(path);
    }
}

void die(char *string) {
    perror(string);
    exit(EXIT_FAILURE);
}

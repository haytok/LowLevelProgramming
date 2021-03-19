#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 2048

void do_cat(char *path);
void die(char *string);

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "%s: file name is not given.\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        do_cat(argv[i]);
    }

    // この方式でファイル名を取得すると、ファイルのメタ情報が出てくるので正しくない。
    // 呼び出し->インクリメント->評価 のサイクルを繰り返す
    // while (*argv) {
    //     do_cat(*argv++);
    // }

    // この書き方だとコアダンプする。
    // 呼び出し->評価->インクリメント のサイクルを繰り返すから？
    // よくよく考えたら、なんかおかしい。
    // puts('\0'); はコアダンプしてしまう。
    // while (*argv++) {
    //     puts(*argv);
    // }

    exit(EXIT_SUCCESS);
}

void do_cat(char *path) {
    unsigned char buf[BUFFER_SIZE];

    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        die(path);
    }

    for (;;) {
        ssize_t read_size = read(fd, buf, sizeof buf);
        if (read_size < 0) {
            die(path);
        }
        if (read_size == 0) {
            break;
        }

        // ssize_t fd_w = write(STDOUT_FILENO, buf, read_size);
        if (write(STDOUT_FILENO, buf, read_size) < 0) {
            die(path);
        }
    }

    if (close(fd) < 0) {
        die(path);
    }
}

void die(char *string) {
    perror(string);
    exit(EXIT_FAILURE);
}

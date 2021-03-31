#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <fcntl.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>

// 全体的な方針
// readdir が返すエントリは、その階層にあるファイルやディレクトリを返すだけである。
// ディレクトリ配下のディレクトリを含め表示するには path 用の領域を確保して、そこに保存するような設計にする。

typedef struct strbuf strbuf;

struct strbuf {
    char *path_name;
    int len;
};

void do_ls(char *path);
void die(char *path);
void print_error(char *message);
strbuf *new_strbuf(void);
strbuf *realloc_strbuf(strbuf *buf, int len);
void traverse(strbuf *buf);

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "%s: no arguments.\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *path = argv[1];
    strbuf *buf = new_strbuf();
    strcpy(buf->path_name, argv[1]);
    traverse(buf);
    exit(EXIT_SUCCESS);
}


// strbuf 用のメモリ領域を確保する関数
// strbuf を初期化する関数
// 追加で全体でエラーを表示する関数の実装
#define INTLEN 1024

strbuf *new_strbuf(void) {
    strbuf *buf;
    buf = (strbuf *)malloc(sizeof(strbuf));
    if (!buf) {
        print_error("malloc(3)");
    }
    buf->path_name = malloc(INTLEN);
    if (!buf->path_name) {
        print_error("malloc(3)");
    }
    buf->len = INTLEN;
    return buf;
}

// strbuf 用に確保した領域を超える場合に、realloc する関数
// strbuf *realloc_strbuf(strbuf *buf, int len) {
//     strbuf *buf;
//     buf = (strbuf *)malloc(INTLEN);
//     if (!buf) {
//         print_error("malloc(3)");
//     }
//     buf->path_name = (char *)malloc(INTLEN);
//     if (!buf->path_name) {
//         print_error("malloc(3)");
//     }
//     buf->len = INTLEN;
//     return buf;
// }

// traverse する関数
void traverse(strbuf *buf) {
    // 第二引数で渡されたディレクトリ名 or ファイル名を出力する
    DIR *dir;
    struct dirent *entry;
    struct stat stat_buf;
    dir = opendir(buf->path_name);
    if (!dir) {
        print_error("opendir(3)");
    }
    puts(buf->path_name);
    while (entry = readdir(dir)) {
        if (strcmp(entry->d_name, ".") == 0) {
            continue;
        }
        if (strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        if (strcmp(buf->path_name, "/") != 0) {
            strcat(buf->path_name, "/");
        }
        strcat(buf->path_name, entry->d_name);

        if (lstat(buf->path_name, &stat_buf) < 0) {
            switch (errno) {
                case ENOENT:
                    break;
                default:
                    print_error("lstat(3)");
            }
        }
        if (S_ISREG(stat_buf.st_mode)) {
            puts(buf->path_name);
        } else if (S_ISDIR(stat_buf.st_mode)) {
            traverse(buf);
        }
        *strrchr(buf->path_name, '/') = '\0';
    }
    closedir(dir);
}

void die(char *path) {
    perror(path);
    exit(EXIT_FAILURE);
}

void print_error(char *message) {
    fprintf(stderr, "%s: %s\n", message, strerror(errno));
    exit(EXIT_FAILURE);
}

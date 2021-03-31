#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

void mkdir_path(char *dir_name);
void die(char *path);

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "%s: no arguments.\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *dir_name = argv[1];
    mkdir_path(dir_name);
    // if (mkdir(dir_name, 0777) < 0) {
    //     die(dir_name);
    // }
    exit(EXIT_SUCCESS);
}

void mkdir_path(char *dir_name) {
    if (mkdir(dir_name, 0777) == 0) {
        return;
    }
    // ディレクトリ自体が存在する時
    if (errno == EEXIST) {
        struct stat st;
        if (stat(dir_name, &st) < 0) die("stat");
        if (!S_ISDIR(st.st_mode)) {
            fprintf(stderr, "file exists but is not a directory: %s\n", dir_name);
        }
        return;
    } else if (errno == ENOENT) {
        // ディレクトリが存在しないとき
        char *parent_path = strdup(dir_name);
        char *last = parent_path + strlen(parent_path) - 1;
        // last にはアドレスが入ってる
        while (*last == '/' && last != parent_path) {
            *last-- = '\0';
        }
        // strrchr の第二引数は int になっているので、文字列 ("") ではなく文字 ('') を渡すべき。
        char *sep = strrchr(parent_path, '/');
        *sep = '\0';
        mkdir_path(parent_path);
        if (mkdir(dir_name, 0777) < 0) die(dir_name);
        return;
    } else {
        die(dir_name);
    }
}

void die(char *path) {
    perror(path);
    exit(EXIT_FAILURE);
}

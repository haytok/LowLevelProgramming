#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <string.h>

void do_ls(char *path);
char *allocate_path_buffer(size_t required_len);
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
        char *buf = allocate_path_buffer(strlen(path) + 1 + strlen(entry->d_name));
        sprintf(buf, "%s/%s", path, entry->d_name);

        struct stat st;
        if (lstat(buf, &st) < 0) {
            die(buf);
        }
        char *t = ctime(&st.st_mtime);

        struct passwd *pw = getpwuid(st.st_uid);
        if (!pw) {
            printf("%s: owner=%s mtime=%s\n", entry->d_name, pw->pw_name, t);
        } else {
            printf("%s: owner=%d mtime=%s\n", entry->d_name, st.st_uid, t);
        }
    }
    if (closedir(dir) < 0) {
        die(path);
    }
}

char *file_path = NULL;
size_t path_len = 0;

char *allocate_path_buffer(size_t required_len) {
    size_t len = path_len;
    while (len < required_len) {
        len += 1024;
    }
    if (len > path_len) {
        if (!file_path) {
            file_path = malloc(len);
            if (!file_path) {
                die("malloc(3)");
            }
        } else {
            char *tmp = realloc(file_path, len);
            if (!tmp) {
                die("realloc");
            }
            file_path = tmp;
        }
    }
    return file_path;
}

void die(char *path) {
    perror(path);
    exit(EXIT_FAILURE);
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 2048

int do_word_count(char *path);
void die(char *string);

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "%s: file name is not given.\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        char *path = argv[i];
        printf("%d %s\n", do_word_count(path), path);
    }

    exit(EXIT_SUCCESS);
}

int do_word_count(char *path) {
    unsigned char buf[BUFFER_SIZE];
    int count = 0;

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

        for (int i = 0; i < read_size; i++) {
            if (buf[i] == '\n') {
                count += 1;
            }
        }
    }

    if (close(fd) < 0) {
        die(path);
    }

    return count;
}

void die(char *string) {
    perror(string);
    exit(EXIT_FAILURE);
}

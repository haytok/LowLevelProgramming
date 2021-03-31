#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char *old_path = argv[1];
    char *new_path = argv[2];
    int fd_open = open(old_path, O_RDONLY);
    int fd_rename = rename(old_path, new_path);
    printf("%d", errno == EXIT_SUCCESS);
}

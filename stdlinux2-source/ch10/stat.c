#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

void die(char *path);
char *get_file_type(mode_t st_mode);

int main(int argc, char **argv) {
    if (argc != 2) {
        die(argv[0]);
    }
    // struct stat *buf;
    // lstat(file_name, buf)
    // の実装は間違い。そんな気もするが、他もそうなのかの実感がない。
    struct stat buf;
    char *file_name = argv[1];
    if (lstat(file_name, &buf) < 0) {
        die(file_name);
    }
    printf("type %s\n", get_file_type(buf.st_mode));
    printf("mode %o\n", buf.st_mode & 0777);
    printf("dev %lx\n", (long)buf.st_dev);
    printf("inode %ld\n", (long)buf.st_ino);
    printf("rdev %lx\n", (long)buf.st_rdev);
    printf("nlink %ld\n", (long)buf.st_nlink);
    printf("uid %ld\n", (long)buf.st_uid);
    printf("gid %ld\n",  (long)buf.st_gid);
    printf("size %lld\n", (long long)buf.st_size);
    printf("block size %lld\n", (long long)buf.st_blksize);
    printf("blocks %lld\n", (long long)buf.st_blocks);
    // char *ctime(const time_t *timep);
    // ctime は引数にポインタが必要なので、 & を付けている。
    printf("Last status change: %s", ctime(&buf.st_ctime));
    printf("Last file access: %s", ctime(&buf.st_atime));
    printf("Last file modification: %s", ctime(&buf.st_mtime));
    exit(EXIT_SUCCESS);
}

void die(char *path) {
    perror(path);
    exit(EXIT_FAILURE);
}

char *get_file_type(mode_t st_mode) {
    if (S_ISREG(st_mode)) {
        return "regular file";
    }
    if (S_ISDIR(st_mode)) {
        return "directory";
    }
    if (S_ISCHR(st_mode)) {
        return "character device";
    }
    if (S_ISBLK(st_mode)) {
        return "block device";
    }
    if (S_ISFIFO(st_mode)) {
        return "FIFO/pipe";
    }
    if (S_ISLNK(st_mode)) {
        return "symlink";
    }
    if (S_ISSOCK(st_mode)) {
        return "socket";
    }
    return "unknown";
}

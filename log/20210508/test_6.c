#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <bits/syscall.h>

int main(void) {
    char *buf = "Hello\n";
    syscall(SYS_write, STDOUT_FILENO, buf, sizeof(buf));
}

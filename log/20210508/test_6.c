#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <asm/unistd_64.h>

int main(void) {
    char *buf = "Hello\n";
    syscall(__NR_write, STDOUT_FILENO, buf, sizeof(buf));
}

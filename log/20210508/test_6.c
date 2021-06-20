#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <asm/unistd_32.h>

int main(void) {
    char *buf = "Hi!\n";
    syscall(__NR_write, STDOUT_FILENO, buf, sizeof(buf));
}

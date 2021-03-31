#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

void die(char *path);

int main(int argc, char **argv) {
    if (argc != 3) {
        die(argv[0]);
    }
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork(2) failed\n");
        exit(EXIT_FAILURE);
    }
    // 子プロセス
    if (pid == 0) {
        execl(argv[1], argv[1], argv[2], NULL);
        perror(argv[1]);
        exit(99);
    } else {
        // 親プロセス
        int status; // この変数に子プロセスの ID が入る。
        waitpid(pid, &status, 0);
        printf("child (PID=%d) finished.\n", pid);
        if (WIFEXITED(status)) {
            printf("exit, status=%d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("signal, sig=%d\n", WTERMSIG(status));
        } else {
            printf("abnormal exit.\n");
        }
        exit(EXIT_SUCCESS);
    }
}

void die(char *path) {
    perror(path);
    exit(EXIT_FAILURE);
}

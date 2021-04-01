#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>

#define PROMPT "$"
#define LINE_BUF_SIZE 2048
#define INIT_CAPA 16

typedef struct cmd cmd;

struct cmd {
    int argc;
    char **args;
};

cmd *read_cmd();
cmd *parse_buf(char *cmd_line);
void invoke_cmd(cmd *cmd);
void free_cmd(cmd *cmd);
void *xmalloc(size_t size);
void die(char *path);
void print_error(char *message);

int main(int argc, char **argv) {
    while (1) {
        struct cmd *cmd;

        fprintf(stdout, PROMPT);
        fflush(stdout);
        cmd = read_cmd();
        if (cmd->argc > 0) {
            invoke_cmd(cmd);
        }
        free_cmd(cmd);
    }
    exit(EXIT_SUCCESS);
}

// 標準入力からコマンド文字列を受け取る関数
cmd *read_cmd() {
    char buf[LINE_BUF_SIZE];
    if (fgets(buf, sizeof buf, stdin) == NULL) {
        exit(EXIT_FAILURE);
    }
    return parse_buf(buf);
}

// 標準入力から受け取った文字列を parse する関数
// cmd_line を for 文で回す
// スペースが来た時に、 cmd で初期化した動的メモリにコマンドとその長さを格納する
cmd *parse_buf(char *cmd_line) {
    char *p = cmd_line;
    cmd *cmd;
    cmd = xmalloc(sizeof cmd);
    cmd->argc = 0;
    cmd->args = xmalloc(sizeof (char * ) * INIT_CAPA);

    while (*p) {
        while (*p && isspace((int)*p)) {
            *p++ = '\0';
        }
        cmd->args[cmd->argc] = p;
        cmd->argc++;
        while (*p && !isspace((int)*p)) {
            p++;
        }
    }
    cmd->args[cmd->argc] = '\0';
    return cmd;
}

void invoke_cmd(cmd *cmd) {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        print_error("fork(2) failded\n");
    }
    // 子プロセス
    if (pid == 0) {
        execv(cmd->args[0], cmd->args);
        print_error("command not found\n");
    } else {
        // 親プロセス
        int status;
        waitpid(pid, &status, 0);
    }
}

void free_cmd(cmd *cmd) {}

void *xmalloc(size_t size) {
    void *tmp;
    tmp = malloc(size);
    if (!tmp) {
        print_error("malloc(3)");
    }
    return tmp;
}

void die(char *path) {
    perror(path);
    exit(EXIT_FAILURE);
}

void print_error(char *message) {
    fprintf(stderr, "%s: %s\n", message, strerror(errno));
    exit(EXIT_FAILURE);
}

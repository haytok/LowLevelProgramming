#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define MAX_LINE_LENGTH 1024


void tail(FILE *file, int n_lines);
unsigned char *read_lines(FILE *file);

// cat tail.c | ./tail 5
int main(int argc, char **argv) {
    if (argc != 2)  {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    tail(stdin, atoi(argv[1]));

    exit(EXIT_SUCCESS);
}

void tail(FILE *file, int n_lines) {
    unsigned char **ring_buffer, **p;
    unsigned char *line;

    ring_buffer = calloc(n_lines, sizeof(char*));
    // メモリ確保ができてるかの確認
    if (!ring_buffer) {
        exit(EXIT_FAILURE);
    }
    // p を進めていく。
    p = ring_buffer;
    while (line = read_lines(file)) {
        // リングバッファなので、*p に値が存在していると、開放して代入する必要がある。
        if (*p) {
            free(*p);
        }
        *p = line;
        // head を進める
        p++;
        if (p >= ring_buffer + n_lines) {
            p = ring_buffer;
        }
    }

    // 出力処理
    if (*p == NULL) {
        p = ring_buffer;
    }

    for (int n = n_lines; n-- && *p; n > 0) {
        printf("%s", *p);
        free(*p);
        // head を進める
        p++;
        if (p >= ring_buffer + n_lines) {
            p = ring_buffer;
        }
    }
    free(ring_buffer);
}

unsigned char *read_lines(FILE *file) {
    size_t buf_len = BUFSIZ;
    unsigned char *head, *p;
    int c;

    head = p = malloc(sizeof(char) * buf_len);
    if (!head) {
        exit(EXIT_FAILURE);
    }
    // malloc 系の処理をしたら、NULL が返ってきていないかの例外処理をの実装
    for (;;) {
        c = fgetc(file);
        // ファイルの終端点に来た時の処理
        if (c == EOF) {
            if (head == p) {
                free(head);
                return NULL;
            }
            break;
        }
        *p++ = c;
        // buf_len (最大容量) を超えてしまったら、再度メモリを確保する。
        if (p >= head + buf_len - 1) {
            buf_len *= 2;
            head = realloc(head, sizeof(char) * buf_len);
            if (!head) {
                exit(EXIT_FAILURE);
            }
        }
        // 改行が来たら切る
        if (c == '\n') {
            break;
        }
    }
    *p++ = '\0';
    return head;
}

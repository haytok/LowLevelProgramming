#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define LINE_BUF_SIZE 1024

typedef void (*sighandler_t)(int);
typedef struct HTTPHeaderField HTTPHeaderField;
typedef struct HTTPRequest HTTPRequest;

struct HTTPHeaderField {
    char *name;
    char *value;
    HTTPHeaderField *next;
};

struct HTTPRequest {
    int protocol_minor_version;
    char *method;
    char *path;
    HTTPHeaderField *header;
    char *body;
    int length;
};

void service(FILE *in, FILE *out, char *docroot);
HTTPRequest *read_request(FILE *in);
void read_request_line(HTTPRequest *req, FILE *in);
void upcase(char *method);

void free_request(HTTPRequest *req);
void *xmalloc(size_t sz);
void log_exit(char *fmt, ...);
void install_signal_handlers(void);
void trap_signal(int sig, sighandler_t handler);
void signal_exit(int sig);

// ./httpd . のようにコマンドを実行する
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <docroot>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    install_signal_handlers();
    printf("Http Server Starts ...\n");
    service(stdin, stdout, argv[1]);
    exit(EXIT_SUCCESS);
}

void service(FILE *in, FILE *out, char *docroot) {
    // 標準入力から http request の解析
    HTTPRequest *req;
    req = read_request(in);
    // response を返す関数
    // request オブジェクトに割り当てられた動的メモリを解放する関数
    // free_request(req);
}

HTTPRequest *read_request(FILE *in) {
    // 変数の初期化
    HTTPRequest *req;
    HTTPHeaderField *h;

    // 動的メモリ領域の確保
    req = xmalloc(sizeof(HTTPRequest));
    req->header = NULL;
    // リクエストライン (GET /index.html HTTP/1.1) を解析して req オブジェクトに書き込む
    read_request_line(req, in);
    // printf("%s \n", req->method); // GET が返ってくるのを確認できる。
    // header の解析
    // body の解析

    return req;
}

void read_request_line(HTTPRequest *req, FILE *in) {
    char buf[LINE_BUF_SIZE];
    char *p, *path;

    if (!fgets(buf, sizeof buf, in)) {
        // エラー処理
        log_exit("no request line");
    }

    // リクエストライン (GET /index.html HTTP/1.1) の GET の解析
    p = strchr(buf, ' ');
    // エラー処理
    if (!p) {
        log_exit("parse error on request line (1): %s", buf);
    }
    *p++ = '\0';
    // メソッド名を確保するための動的メモリの確保
    req->method = xmalloc(p - buf);
    strcpy(req->method, buf);
    upcase(req->method);

    // リクエストライン (GET /index.html HTTP/1.1) の /index.html の解析
    path = p;
    p = strchr(path, ' ');
    // エラー処理
    if (!p) {
        log_exit("parse error on request line (2): %s", buf);
    }
    *p++ = '\0';
    req->path = xmalloc(p - path);
    strcpy(req->path, path);

    // リクエストライン (GET /index.html HTTP/1.1) の HTTP/1.1 の解析
    if (strncasecmp(p, "HTTP/1.", strlen("HTTP/1.")) != 0) {
        log_exit("parse error on request line (3): %s", buf);
    }
    p += strlen("HTTP/1.");
    req->protocol_minor_version = atoi(p);
}

void upcase(char *method) {
    char *p;
    for (p = method; *p; p++) {
        *p = (char)toupper((int)*p);
    }
}

void free_request(HTTPRequest *req) {
    HTTPHeaderField *header, *h;
    header = req->header;
    while (header) {
        h = header;
        header = header->next;
        free(h->name);
        free(h->value);
        free(h);
    }
    free(req->method);
    free(req->path);
    free(req->body);
    free(req);
}

void *xmalloc(size_t sz) {
    void *p;
    p = malloc(sz);
    if (!p) {
        log_exit("failed to allocate memory");
    }
    return p;
}

void log_exit(char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fputc('\n', stderr);
    va_end(ap);
    exit(EXIT_FAILURE);
}

void install_signal_handlers(void) {
    trap_signal(SIGPIPE, signal_exit);
}

void trap_signal(int sig, sighandler_t handler) {
    struct sigaction act;

    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
    if (sigaction(sig, &act, NULL) < 0) {
        log_exit("sigaction() failded: %s", strerror(errno));
    }
}

void signal_exit(int sig) {
    log_exit("exit by signal %d\n", sig);
}

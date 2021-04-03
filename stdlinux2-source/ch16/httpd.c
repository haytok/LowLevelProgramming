#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>

#define LINE_BUF_SIZE 1024
#define MAX_REQUEST_BODY_LENGTH (1024 * 1024)
#define BLOCK_BUF_SIZE 1024

#define SERVER_NAME "LittleHTTP"
#define SERVER_VERSION "1.0"
#define HTTP_MINOR_VERSION 0
#define TIME_BUF_SIZE 6

typedef void (*sighandler_t)(int);
typedef struct HTTPHeaderField HTTPHeaderField;
typedef struct HTTPRequest HTTPRequest;
typedef struct FileInfo FileInfo;

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
    long length;
    char *body;
};

struct FileInfo {
    char *path;
    long size;
    int ok;
};

void service(FILE *in, FILE *out, char *docroot);
HTTPRequest *read_request(FILE *in);
void read_request_line(HTTPRequest *req, FILE *in);
void upcase(char *method);
HTTPHeaderField *read_header_field(FILE *in);
long content_length(HTTPRequest *req);
char *lookup_header_field_value(HTTPRequest *req, char *name);
void respond_to(HTTPRequest *req, FILE *out, char *docroot);
void do_file_response(HTTPRequest *req, FILE *out, char *docroot);
FileInfo *get_fileinfo(char *docroot, char *path);
char *build_fspath(char *docroot, char *path);
void free_fileinfo(FileInfo *info);
char *guess_content_type(FileInfo *info);
void output_common_header_fields(HTTPRequest *req, FILE *out, char *status);
void not_found(HTTPRequest *req, FILE *out);
void method_not_allowed(HTTPRequest *req, FILE *out);
void not_implemented(HTTPRequest *req, FILE *out);

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
    respond_to(req, out, docroot);
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

    // // printf("%s \n", req->method); // GET が返ってくるのを確認できる。
    // printf("strlen: %ld\n", strlen("test\r\n")); // 6 が表示される
    // char test[LINE_BUF_SIZE];
    // test[0] = '\n';
    // // strcmp の第二引数にはポインタを渡す必要があるので、'' ではなく、"" で値を渡す。
    // // この点に留意していれば以下のどちらの比較方式を用いても問題ない
    // printf("%d\n", (test[0] == '\n'));
    // printf("%d\n", (strcmp(test, "\n") == 0));

    // header の解析して、HTTPRequest オブジェクトの header フィールドに値を設定
    while (h = read_header_field(in)) {
        h->next = req->header;
        req->header = h;
    }
    // body の解析
    req->length = content_length(req);
    // printf("length %ld\n", req->length);
    // req->length に従って HTTPRequest オブジェクトの body フィールドにメモリ容易機を確保する。
    if (req->length != 0) {
        if (req->length > MAX_REQUEST_BODY_LENGTH) {
            log_exit("request body too long");
        }
        req->body = xmalloc(req->length);
        if (fread(req->body, req->length, 1, in) < 1) {
            log_exit("failed to read request body");
        }
    } else {
        req->body = NULL;
    }

    return req;
}

// HTTPRequest オブジェクトの method, path, protocol_minor_version に値を設定
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

// 入力ストリームのヘッダー箇所を (Connection: close\r\n) 解析し、HTTPHeaderField　オブジェクトを返す
HTTPHeaderField *read_header_field(FILE *in) {
    HTTPHeaderField *h;
    char buf[LINE_BUF_SIZE];
    char *p;

    if (!fgets(buf, sizeof buf, in)) {
        log_exit("failed to read request header field: %s\n", strerror(errno));
    }
    // 改行や \r\n が来た際には、NULL を返す
    if ((strcmp(buf, "\n") == 0) || (strcmp(buf, "\r\n") == 0)) {
        return NULL;
    }

    // ヘッダー (Connection: close\r\n) の Connection の解析
    p = strchr(buf, ':');
    if (!p) {
        log_exit("parse error on request header field: %s", buf);
    }
    *p++ = '\0';
    h = xmalloc(sizeof(HTTPHeaderField));
    h->name = xmalloc(p - buf);
    strcpy(h->name, buf);

    // ヘッダー (Connection: close\r\n) の close の解析
    p += strspn(p, " \t");
    h->value = xmalloc(strlen(p) + 1);
    strcpy(h->value, p);

    return h;
}

long content_length(HTTPRequest *req) {
    char *value;
    int length;

    value = lookup_header_field_value(req, "Content-Length");
    if (!value) {
        return 0;
    }

    length = atol(value);
    if (length < 0) {
        log_exit("negative Content-Length value");
    }
    return length;
}

char *lookup_header_field_value(HTTPRequest *req, char *name) {
    HTTPHeaderField *h;

    for (h = req->header; h; h = h->next) {
        if (strcmp(h->name, name) == 0) {
            return h->value;
        }
    }
    return NULL;
}

void respond_to(HTTPRequest *req, FILE *out, char *docroot) {
    // リクエストタイプ (GET / HEAD / POST / 不適切な形式) で条件分岐をする
    if (strcmp(req->method, "GET") == 0) {
        do_file_response(req, out, docroot);
    } else if (strcmp(req->method, "HEAD") == 0) {
        do_file_response(req, out, docroot);
    } else if (strcmp(req->method, "POST") == 0) {
        method_not_allowed(req, out);
    } else {
        not_implemented(req, out);
    }
}

// 現状の実装では、GET / HEAD リクエストで呼び出される
void do_file_response(HTTPRequest *req, FILE *out, char *docroot) {
    FileInfo *info;

    // get_fileinfo を実装しつつ、build_fspath を実装する
    info = get_fileinfo(docroot, req->path);
    if (!info->ok) {
        free_fileinfo(info);
        // 未実装
        not_found(req, out);
        return;
    }
    output_common_header_fields(req, out, "200 OK");
    fprintf(out, "Content-Length: %ld\r\n", info->size);
    fprintf(out, "Content-Type: %s\r\n", guess_content_type(info));
    fprintf(out, "\r\n");
    if (strcmp(req->method, "HEAD") != 0) {
        int fd;
        char buf[BLOCK_BUF_SIZE];
        ssize_t n;
        fd = open(info->path, O_RDONLY);
        if (fd < 0) {
            log_exit("failded to open %s: %s", info->path, strerror(errno));
        }
        for (;;) {
            n = read(fd, buf, BLOCK_BUF_SIZE);
            if (n < 0) {
                log_exit("failded to read %s: %s", info->path, strerror(errno));
            }
            if (n == 0) {
                break;
            }
            if (fwrite(buf, n, 1, out) < n) {
                // printf("debug: %s", info->path);
                log_exit("failded to write to socket: %s", info->path, strerror(errno));
            }
        }
        close(fd);
    }
    fflush(out);
    free_fileinfo(info);
}

FileInfo *get_fileinfo(char *docroot, char *path) {
    FileInfo *info;
    struct stat st;

    info = xmalloc(sizeof(FileInfo));
    info->path = build_fspath(docroot, path);
    info->ok = 0;
    if (lstat(info->path, &st) < 0) {
        return info;
    }
    if (!S_ISREG(st.st_mode)) {
        return info;
    }
    info->ok = 1;
    info->size = st.st_size;
    return info;
}

char *build_fspath(char *docroot, char *urlpath) {
    char *path;

    path = xmalloc(strlen(docroot) + 1 + strlen(urlpath) + 1);
    sprintf(path, "%s/%s", docroot, urlpath);
    return path;
}

void free_fileinfo(FileInfo *info) {
    free(info->path);
    free(info);
}

char *guess_content_type(FileInfo *info) {
    return "text/plain";
}

void output_common_header_fields(HTTPRequest *req, FILE *out, char *status) {
    time_t t;
    struct tm *tm;
    char buf[TIME_BUF_SIZE];

    t = time(NULL);
    tm = gmtime(&t);
    if (!tm) log_exit("gmtime() failed: %s", strerror(errno));
    strftime(buf, TIME_BUF_SIZE, "%a, %d %b %Y %H:%M:%S GMT", tm);
    fprintf(out, "HTTP/1.%d %s\r\n", HTTP_MINOR_VERSION, status);
    fprintf(out, "Date: %s\r\n", buf);
    fprintf(out, "Server: %s/%s\r\n", SERVER_NAME, SERVER_VERSION);
    fprintf(out, "Connection: close\r\n");
}

void not_found(HTTPRequest *req, FILE *out) {
    output_common_header_fields(req, out, "404 Not Found");
    fprintf(out, "Content-Type: text/html\r\n");
    fprintf(out, "\r\n");
    if (strcmp(req->method, "HEAD") != 0) {
        fprintf(out, "<html>\r\n");
        fprintf(out, "<header><title>Not Found</title><header>\r\n");
        fprintf(out, "<body><p>File not found</p></body>\r\n");
        fprintf(out, "</html>\r\n");
    }
    fflush(out);
}

void method_not_allowed(HTTPRequest *req, FILE *out) {
    output_common_header_fields(req, out, "405 Method Not Allowed");
    fprintf(out, "Content-Type: text/html\r\n");
    fprintf(out, "\r\n");
    fprintf(out, "<html>\r\n");
    fprintf(out, "<header>\r\n");
    fprintf(out, "<title>405 Method Not Allowed</title>\r\n");
    fprintf(out, "<header>\r\n");
    fprintf(out, "<body>\r\n");
    fprintf(out, "<p>The request method %s is not allowed</p>\r\n", req->method);
    fprintf(out, "</body>\r\n");
    fprintf(out, "</html>\r\n");
    fflush(out);
}

void not_implemented(HTTPRequest *req, FILE *out) {
    output_common_header_fields(req, out, "501 Not Implemented");
    fprintf(out, "Content-Type: text/html\r\n");
    fprintf(out, "\r\n");
    fprintf(out, "<html>\r\n");
    fprintf(out, "<header>\r\n");
    fprintf(out, "<title>501 Not Implemented</title>\r\n");
    fprintf(out, "<header>\r\n");
    fprintf(out, "<body>\r\n");
    fprintf(out, "<p>The request method %s is not implemented</p>\r\n", req->method);
    fprintf(out, "</body>\r\n");
    fprintf(out, "</html>\r\n");
    fflush(out);
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

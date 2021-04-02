#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

int open_connection(char *host, char *service);

int main(int argc, char **argv) {
    int socket;
    FILE *f;
    char buf[1024];

    char *msg = argv[1];

    socket = open_connection("localhost", "echo");
    f = fdopen(socket, "w+");
    if (!f) {
        perror("fdopen(3)");
        exit(EXIT_FAILURE);
    }

    fprintf(f, "%s\n", msg);
    fflush(f);

    fgets(buf, sizeof buf, f);
    fclose(f);
    fputs(buf, stdout);
    exit(EXIT_SUCCESS);
}

int open_connection(char *host, char *service) {
    int sock;
    // getaddrinfo でホスト名とサービス名から IP アドレスとポート番号を得る。
    struct addrinfo hints, *res, *ai;
    int err;
    // hints (候補を絞り込むための条件) の初期化
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((err = getaddrinfo(host, service, &hints, &res) != 0)) {
        fprintf(stderr, "getaddrinfo(3) %s\n", gai_strerror(err));
        exit(EXIT_FAILURE);
    }
    for (ai = res; ai; ai = ai->ai_next) {
        sock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (socket < 0) {
            continue;
        }
        if (connect(sock, ai->ai_addr, ai->ai_addrlen) < 0) {
            close(sock);
            continue;
        }
        // socket の作成に成功
        freeaddrinfo(res);
        return sock;
    }
    fprintf(stderr, "socket(2)/connect(2) failed\n");
    freeaddrinfo(res);
    exit(EXIT_FAILURE);
}

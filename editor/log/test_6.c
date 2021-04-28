#include <stdio.h>
#include <unistd.h>

void progress() {
    static int pos = 0;
    static char mark[] = {'-', '\\', '|', '/'};
    fprintf(stderr, "\r%c", mark[pos]);
    pos = (pos + 1) % sizeof(mark);
}

int main(void) {
    int i, j;
    fprintf(stderr, "0%%       50%%       100%%\n");
    fprintf(stderr, "+---------+---------+\n");
    for (i = 0; i <= 100; i++) {
        for (j = 0; j < i / 5 + 1; j++) {
            fprintf(stderr, "##");
        }
        fprintf(stderr, "\n");
        fprintf(stderr, "%3d%%\n", i);
        usleep(100000);
        fprintf(stderr, "\033[2A");
    }
    printf("\nfinish!!!\n");
}

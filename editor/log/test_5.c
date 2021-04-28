#include <stdio.h>
#include <unistd.h>

void progress() {
    static int pos = 0;
    static char mark[] = {'-', '\\', '|', '/'};
    fprintf(stderr, "\r%c", mark[pos]);
    pos = (pos + 1) % sizeof(mark);
}

int main(void) {
    int i;
    for (i = 0; i < 10; i++) {
        progress();
        usleep(500000);
    }
    printf("\nfinish!!!\n");
}

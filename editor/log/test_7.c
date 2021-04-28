#include <stdio.h>
#include <unistd.h> // Unix Standard Header の略称らしい。

int main() {
    fprintf(stderr, "1234567890");
    sleep(1);
    fprintf(stderr, "\033[5G");
    // 消してから改行刷るか、いきなりシュッと消すか
    sleep(1);
    fprintf(stderr, "\033[K");
}

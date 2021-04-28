#include <stdio.h>
#include <unistd.h> // Unix Standard Header の略称らしい。

int main() {
    fprintf(stderr, "1234567890");
    sleep(1);
    fprintf(stderr, "\033[5G");
    // 消してから改行刷るか、いきなりシュッと消すか
    sleep(1);
    fprintf(stderr, "\033[K");
    sleep(1);
    // カーソルの前、後ろ、全体を消去する
    fprintf(stderr, "\033[2J");
    // カーソルを原点に移動させる
    // clear のような挙動を実現できる。
    fprintf(stderr, "\033[2J");
    // 以下のようにまとめて書くこともできる、
    // また、\033 を \e と記述しても可。
    // fprintf(stderr, "\e[2J\033[0;0H");
    sleep(1);
}

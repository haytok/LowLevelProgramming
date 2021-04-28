#include <stdio.h>
#include <unistd.h>

int main(void) {
    int i;
    for (i = 0; i < 20; i++) {
        // printf だと、以下の # が表示されなかった。
        // 標準出力の場合には出力バッファがあるので、改行コードを出力するまでには、画面に反映されない可能性がある。
        // したがって、標準エラー出力を使用する。
        // printf("_");
        fprintf(stderr, "#");
        usleep(500000);
    }
    printf("\nfinish!!!\n");
}

#include <stdio.h>
#include <stdlib.h>

int plus(int n) {
    return n + 1;
}

int main() {
    int input = 0;
    // int 型の値を受け取って、int へのポインタを返す変数
    int (*f)(int) = plus;
    printf("%d\n", plus(input));
    exit(EXIT_SUCCESS);
}

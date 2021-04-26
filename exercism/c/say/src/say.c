#include "say.h"

int say(int64_t input, char **ans) {
    if (input < 0 || input >= pow(10, 12)) {
        return -1;
    }
    char *a[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    char *b[] = { "ten","twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
    char *c[] = { "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
    *ans = malloc(sizeof(char *) * 1024);
    // この実装が難しかった。C 言語 関数 文字列 参照渡し でググった。
    if (input == 0) {
        strcpy(*ans, "zero");
        return 0;
    }
    int d = input / 100;
    int e = (input - d * 100) / 10;
    int f = (input - d * 100) % 10;
    // if (input < 10) {
    //     strcpy(*ans, a[input]);
    //     return 0;
    // }
    if (input >= 11 && input <= 19) {
        strcpy(*ans, c[input-11]);
        return 0;
    }
    return 0;
}

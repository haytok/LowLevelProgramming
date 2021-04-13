#include "roman_numerals.h"

char *to_roman_numeral(unsigned int number) {
    char *input = malloc(sizeof(char *) * 1024);
    memset(input, '\0', 1024);
    int a[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char *r[13]={"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    number = (int)number;

    if (number > 0 && number < 4000) {
        for (int i = 0; i < 13; i++) {
            while((int)number >= a[i]) {
                strcat(input, r[i]);
                number -= a[i];
            }
        }
    }
    return input;
}

// 前回の計算結果が残っている際に必要な初期化処理
// char *res = malloc(sizeof(char *) * 1024);
// memset(res, '\0', 1024);

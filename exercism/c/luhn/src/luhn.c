#include "luhn.h"

bool luhn(const char *num) {
    if (strcmp(num, "0") == 0) {
        return false;
    }
    int i = 0;
    int ans = 0;
    char *head;
    head = malloc(sizeof(char) * 1024);
    strcpy(head, num);
    rev_string(head);
    while (*head) {
        // 一文字ずつ index を使って処理をしても解ける。
        // printf("In while, %c\n", num[i]);
        char *tmp;
        tmp = malloc(sizeof(char));
        strncpy(tmp, head, 1);
        if (isalpha(*tmp) != 0) {
            return false;
        }
        if (strcmp(tmp, " ") == 0) {
            head++;
            continue;
        }
        int value = atoi(tmp);
        if (i % 2 == 1) {
            ans += (value * 2 > 9) ? value * 2 - 9 : value * 2;
        } else {
            ans += value;
        }
        head++;
        i++;
    }
    if (i == 1 && ans == 0) {
        return false;
    }
    return ans % 10 == 0 ? true : false;
}

unsigned str_length(const char str[]) {
    unsigned len = 0;
    while (str[len])
        len++;
    return (len);
}

void rev_string(char str[]) {
    int i;
    int len = str_length(str);
    for (i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
}

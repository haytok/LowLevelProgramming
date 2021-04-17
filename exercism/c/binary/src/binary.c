#include "binary.h"

int convert(const char *input) {
    int ans, index;
    char *head;

    ans = 0;
    index = strlen(input) - 1;
    head = malloc(sizeof(char) * 1024);
    memcpy(head, input, strlen(input));

    while (*head) {
        char *buf = malloc(sizeof(char) * 1);
        strncpy(buf, head, 1);
        if (strcmp(buf, "2") == 0 || isalpha(*buf) != 0) {
            return INVALID;
        }
        ans += (int)pow(2, (index)) * atoi(buf);
        index--;
        head++;
    }

    return ans;
}

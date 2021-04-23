#include "largest_series_product.h"

int64_t largest_series_product(char *digits, size_t span) {
    if ((int)span < 0) {
        return -1;
    }
    int ans = -1;
    int end_index = strlen(digits) - (int)span + 1;
    for (int i = 0; i < end_index; i++) {
        int value = 1;
        for (int j = i; j < i + (int)span; j++) {
            if (isalpha(digits[j])) {
                return -1;
            }
            char *buf;
            buf = malloc(sizeof(char) * 1);
            sprintf(buf, "%c", digits[j]);
            value *= atoi(buf);
        }
        if (ans < value) {
            ans = value;
        }
        value = 1;
    }
    return (int64_t)ans;
}

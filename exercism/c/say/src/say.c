#include "say.h"

int say(int64_t input, char **ans) {
    if (input < 0 || input >= pow(10, 12)) {
        return -1;
    }
    *ans = malloc(sizeof(char *) * 1024);
    // この実装が難しかった。C 言語 関数 文字列 参照渡し でググった。
    strcpy(*ans, num2words(input));
    return 0;
}

char *num2words(int64_t num) {
    char *nums_20_90[] = {"twenty", "thirty",  "forty",  "fifty",
                          "sixty",  "seventy", "eighty", "ninety"};
    char *nums_0_19[] = {"zero",    "one",       "two",      "three",
                         "four",    "five",      "six",      "seven",
                         "eight",   "nine",      "ten",      "eleven",
                         "twelve",  "thirteen",  "fourteen", "fifteen",
                         "sixteen", "seventeen", "eighteen", "nineteen"};
    if (num < 20) {
        return nums_0_19[num];
    }
    char *buf;
    buf = malloc(sizeof(char) * 1024);
    if (num < 100) {
        if (num % 10 == 0) {
            sprintf(buf, "%s", nums_20_90[num / 10 - 2]);
        } else {
            sprintf(buf, "%s-%s", nums_20_90[num / 10 - 2], nums_0_19[num % 10]);
        }
        return buf;
    }
    nums_dict_t max_key = get_max_key(num);
    if (num % max_key.value == 0) {
        sprintf(buf, "%s %s", num2words(num / max_key.value), max_key.key);
    } else {
        sprintf(buf, "%s %s %s", num2words(num / max_key.value), max_key.key, num2words(num % max_key.value));
    }
    return buf;
}

nums_dict_t get_max_key(int64_t num) {
    nums_dict_t nums_dict[] = {
        (nums_dict_t){.key="hundred", .value=100},
        (nums_dict_t){.key="thousand", .value=1000},
        (nums_dict_t){.key="million", .value=1000000},
        (nums_dict_t){.key="billion", .value=1000000000}
    };
    nums_dict_t max_key = nums_dict[0];
    for (int i = 1; i < (int)(sizeof(nums_dict)/sizeof(nums_dict[0])); i++) {
        if (nums_dict[i].value <= num) {
            max_key = max_key.value > nums_dict[i].value ? max_key : nums_dict[i];
        }
    }
    return max_key;
}

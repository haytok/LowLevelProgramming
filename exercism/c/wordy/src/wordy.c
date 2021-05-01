#include "wordy.h"

bool answer(const char *question, int *result) {
    char *copy_q = strdup(question);
    int ans = 0;
    char *cal = malloc(sizeof(char) * 1024);
    *result = -1;

    while (*copy_q) {
        if (isspace(*copy_q)) {
            copy_q++;
        }

        if (*copy_q == '-') {
            copy_q++;

            int value = (int)strtol(copy_q, &copy_q, 10);
            value = (value * (-1));
            if (strcmp(cal, "plus") == 0) {
                ans += value;
            }  else if (strcmp(cal, "minus") == 0) {
                ans -= value;
            } else if ((strcmp(cal, "multiplied") == 0)) {
                ans *= value;
            } else if (strcmp(cal, "divided") == 0) {
                ans /= value;
            } else {
                ans = value;
            }

            free(cal);
            cal = malloc(sizeof(char) * 1024);

            continue;
        }

        if (isdigit(*copy_q)) {
            int value = (int)strtol(copy_q, &copy_q, 10);
            if (strlen(cal) != 0) {
                cal_value(&ans, cal, value);
            } else {
                // この実装は良くない。
                if (ans == 0) {
                    ans = value;
                } else {
                    return false;
                }
            }

            free(cal);
            cal = malloc(sizeof(char) * 1024);

            continue;
        }

        char *keyword;
        keyword = malloc(sizeof(char) * 1024);
        if ((keyword = starts_with_reserved(copy_q))) {
            if (
                strcmp(keyword, "plus") == 0
                || strcmp(keyword, "minus") == 0
                || strcmp(keyword, "multiplied") == 0
                || strcmp(keyword, "divided") == 0
            ) {
                // plus plus の文字列が続くケースの時は、Invalid で弾く。
                if (strlen(cal) != 0) {
                    return false;
                }

                strcpy(cal, keyword);
                copy_q += strlen(keyword);
                continue;
            } else if (
                strcmp(keyword, "What") == 0
                || strcmp(keyword, "is") == 0
                || strcmp(keyword, "?") == 0
                || strcmp(keyword, "by") == 0
            ) {
                copy_q += strlen(keyword);
                continue;
            } else {
                return false;
            }
        }
    }
    printf("ans %d, cal %s\n", ans, cal);
    // 良くない実装
    if (strlen(cal) || ans == 0) {
        return false;
    }
    // 参照渡しの変数に値を書き込みたい時はこの書き方をする。
    *result = ans;
    return true;
}

// p (長い、ベース) と q を比較する。
bool startswith(char *p, char *q) {
    return memcmp(p, q, strlen(q)) == 0;
}

char *starts_with_reserved(char *string) {
    // printf("string %s\n", string);
    static char *keyword[] = {
        "What",
        "is",
        "?",
        "plus",
        "minus",
        "multiplied",
        "divided",
        "by"
    };
    int keyword_size = sizeof(keyword) / sizeof(*keyword);
    for (int i = 0; i < keyword_size; i++) {
        if (startswith(string, keyword[i])) {
            return keyword[i];
        }
    }
    return "";
}

void cal_value(int *ans, char *cal, int value) {
    if (strcmp(cal, "plus") == 0) {
        *ans += value;
    }  else if (strcmp(cal, "minus") == 0) {
        *ans -= value;
    } else if (strcmp(cal, "multiplied") == 0) {
        *ans *= value;
    } else if (strcmp(cal, "divided") == 0) {
        *ans /= value;
    }
}

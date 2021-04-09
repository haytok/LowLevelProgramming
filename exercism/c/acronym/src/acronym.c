#include "acronym.h"

char *abbreviate(const char *phrase) {
    if (!phrase || memcmp(phrase, "", 1) == 0) {
        return NULL;
    }
    char *actual, *head;
    bool flag;
    head = malloc(sizeof(char *) * 1024);
    flag = false;
    actual = malloc(sizeof(char));
    // The  strcat()  function  appends  the src string to the dest string.
    strncat(actual, phrase, 1);
    // phrase に const 演算子が付いてるので、先頭のポインタをコピー
    memcpy(head, phrase, 1024);
    while(*head) {
        if (
            memcmp(head, " ", 1) == 0 ||
            memcmp(head, "-", 1) == 0 ||
            memcmp(head, "_", 1) == 0
        ) {
            flag = true;
            head++;
            continue;
        }
        if (flag) {
            strncat(actual, head, 1);
            flag = false;
        }
        head++;
    }
    upcase(actual);
    printf("actual: %s\n", actual);
    return actual;
}

void upcase(char *actual) {
    char *p;
    for (p = actual; *p; p++) {
        *p = (char)toupper((int)*p);
    }
}

// const char* p = phrase; として、while 文で回していくのでも OK !
// char *abbreviate(const char *phrase)
// {
//     const char* p = phrase;
//     if (p == NULL || *p == 0)
//         return NULL;
//     int start = 1;
//     char* result = malloc(strlen(phrase));
//     char* r = result;
//     while (*p != 0) {
//         if (!isalnum(*p) ) {
//             start = 1;
//         }
//         else if (start) {
//             *r++ = toupper(*p);
//             start = 0;
//         }
//         p++;
//     }
//     *r = 0;
//     return result;
// }

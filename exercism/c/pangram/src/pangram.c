#include "pangram.h"

bool is_pangram(const char *sentence) {
    if (!sentence) {
        return false;
    }
    bool alphabet[ALPHABET_COUNTS] = {false};
    char *head;
    head = malloc(sizeof(char *) * 1024);
    memcpy(head, sentence, 1024);
    lowcase(head);
    while (*head) {
        if (*head == ' ' || *head == '_' || isdigit(*head) != 0 || *head == '.' || *head == '\"') {
            head++;
            continue;
        }
        int index = *head - 'a';
        alphabet[index] = true;
        // printf("head %c %d\n", *head, index);
        head++;
    }
    for (int i = 0; i < ALPHABET_COUNTS; i++) {
        // printf("%c %d\n", i + 'a', alphabet[i]);
        if (!alphabet[i]) {
            return false;
        }
    }
    return true;
}

void lowcase(char *actual) {
    char *p;
    for (p = actual; *p; p++) {
        *p = (char)tolower((int)*p);
    }
}

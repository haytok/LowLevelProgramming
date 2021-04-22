#include "atbash_cipher.h"

char *atbash_encode(char *input) {
    char dec[LENGTH];
    for (int i = LENGTH - 1; i >= 0; i--) {
        dec[LENGTH - i - 1] = 'a' + i;
    }
    int length = strlen(input);
    char *ans;
    ans = malloc(sizeof(char) * length);
    int write_index = 0;
    int counts = 0;
    for (int i = 0; i < length; i++) {
        // char buf[] で宣言した時の NULL 文字が抜けてた。
        if (i == length - 1) {
            ans[write_index] = '\0';
        }
        if (isspace(input[i]) || input[i] == ',' || input[i] == '.') {
            continue;
        }
        if (isdigit(input[i])) {
            ans[write_index++] = input[i];
            counts++;
            if (counts > 0 && counts % 5 == 0 && i != length - 1) {
                ans[write_index++] = ' ';
                counts = 0;
                continue;
            }
        }
        if (isalpha(input[i])) {
            int index = tolower(input[i]) - 'a';
            ans[write_index++] = dec[index];
            counts++;
        }
        if (counts > 0 && counts % 5 == 0 && i != length - 2) {
            ans[write_index++] = ' ';
            counts = 0;
            continue;
        }
    }
    return ans;
}

char *atbash_decode(const char *input) {
    char enc[LENGTH];
    for (int i = 0; i < LENGTH; i++) {
        enc[i] = 'a' + i;
    }
    int length = strlen(input);
    char *ans;
    ans = malloc(sizeof(char) * length);
    int write_index = 0;
    int i = 0;
    for (i = 0; i < length; i++) {
        if (isspace(input[i])) {
            continue;
        }
        if (isdigit(input[i])) {
            ans[write_index++] = input[i];
        }
        if (isalpha(input[i])) {
            int index = get_index(input[i]);
            ans[write_index++] = enc[index];
        }
    }
    // NULL 文字がないと、変な文字も書き込まれて、テストケースが通らない。
    ans[write_index] = '\0';
    return ans;
}

void lowcase(char *method) {
    char *p;
    for (p = method; *p; p++) {
        *p = (char)tolower((int)*p);
    }
}

int get_index(int value) {
    char dec[LENGTH];
    for (int i = LENGTH - 1; i >= 0; i--) {
        dec[LENGTH - i - 1] = 'a' + i;
    }
    for (int i = 0; i < LENGTH; i++) {
        if (dec[i] == value) {
            return i;
        }
    }
    return -1;
}

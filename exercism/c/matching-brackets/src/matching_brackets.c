#include "matching_brackets.h"

bool is_paired(const char *input) {
    int length = strlen(input);
    int *left_sets;
    int left_index = 0;
    left_sets = malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++) {
        if (
            isspace(input[i])
             || isdigit(input[i])
             || isalpha(input[i])
             || input[i] == '+'
             || input[i] == '-'
             || input[i] == '*'
             || input[i] == '/'
             || input[i] == '^'
             || input[i] == '.'
             || input[i] == '\\'
             || input[i] == '&'
        ) {
            continue;
        }
        int value = get_value(input[i]);
        if (value > 2) {
            if (get_pair(value) == left_sets[--left_index]) {
                continue;
            } else {
                return false;
            }
        } else {
            left_sets[left_index++] = value;
        }
    }
    return left_index == 0 ? true : false;
}

int get_value(int c) {
    if (c == '[') {
        return 0;
    } else if (c == '(') {
        return 1;
    } else if (c == '{') {
        return 2;
    } else if (c == '}') {
        return 3;
    } else if (c == ')') {
        return 4;
    } else if (c == ']') {
        return 5;
    }
    return -1;
}

int get_pair(int value) {
    if (value == 5) {
        return 0;
    } else if (value == 4) {
        return 1;
    } else if (value == 3) {
        return 2;
    }
    return -1;
}

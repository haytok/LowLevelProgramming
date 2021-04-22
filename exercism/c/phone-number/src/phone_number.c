#include "phone_number.h"

char *phone_number_clean(const char *input) {
    printf("input %s\n", input);
    char *ans;
    ans = malloc(sizeof(char) * 9);
    int length = strlen(input);
    int counts = 0;
    bool is_left_round_bracket = false;
    bool is_right_round_bracket = false;
    for (int i = 0; i < length; i++) {
        if (input[i] == '(') {
            is_left_round_bracket = true;
            continue;
        }
        if (input[i] == ')') {
            is_right_round_bracket = true;
            continue;
        }
        if (
            isspace(input[i])
            || input[i] == '-'
            || input[i] == '.'
            || input[i] == '+'
        ) {
            continue;
        }
        // 不適切な文字を検知
        if (
            isalpha(input[i])
            || input[i] == '@'
            || input[i] == ':'
            || input[i] == '!'
        ) {
            strcpy(ans, "0000000000");
            return ans;
        }
        if (is_left_round_bracket) {
            if (input[i] >= '2' && input[i] <= '9') {
                ans[counts++] = input[i];
                is_left_round_bracket = false;
                continue;
            } else {
                strcpy(ans, "0000000000");
                return ans;
            }
        }
        if (is_right_round_bracket) {
            if (input[i] >= '2' && input[i] <= '9') {
                ans[counts++] = input[i];
                is_right_round_bracket = false;
                continue;
            } else {
                strcpy(ans, "0000000000");
                return ans;
            }
        }
        ans[counts++] = input[i];
    }
    // printf("counts %d\n", counts);
    if (counts != 10) {
        if (counts == 11 && ans[0] == '1') {
            counts = 0;
            // printf("length %d, ans %s\n", length, ans);
            char *update_ans;
            update_ans = malloc(sizeof(char) * 9);
            for (int j = 1; j < length; j++) {
                // printf("counts %d, j %d, char %c\n", counts, j, input[j]);
                update_ans[counts++] = ans[j];
                // printf("ans %c\n", ans[counts]);
                counts++;
            }
            return update_ans;
        } else {
            strcpy(ans, "0000000000");
        }
    }
    return ans;
}

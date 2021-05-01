#include "rail_fence_cipher.h"

char *encode(char *text, size_t rails) {
    int *steps = get_step(rails);

    int input_length = strlen(text);
    char *ans = malloc(sizeof(char) * 1024);
    char **tmp = malloc(sizeof(char) * 1024);
    for (int i = 0; i < (int)steps[0]; i++) {
        tmp[i] = malloc(sizeof(char) * 1024);
    }

    int counts = -1;
    for (int i = 0; i < input_length; i++) {
        if (i % (steps[0]) == 0) {
            counts++;
        }
        int index = 0;
        if (i >= steps[0]) {
            index = i - steps[0] * counts;
        } else {
            index = i;
        }
        if (index >= (int)rails) {
            index = steps[0] - index;
        }
        char *buf = malloc(sizeof(char) * 1);
        sprintf(buf, "%c", text[i]);
        strcat(tmp[index], buf);
    }

    for (int i = 0; i < (int)steps[0]; i++) {
        strcat(ans, tmp[i]);
    }

    return ans;
}

char *decode(char *ciphertext, size_t rails) {
    int *steps = get_step(rails);

    int input_length = strlen(ciphertext);
    char *ans = malloc(sizeof(char) * input_length);

    int k = 0;
    int *indexes = malloc(sizeof(int) * input_length);
    for (int j = 0; j < (int)rails; j++) {
        int counts = -1;
        for (int i = 0; i < input_length; i++) {
            if (i % (steps[0]) == 0) {
                counts++;
            }
            int index = 0;
            if (i >= steps[0]) {
                index = i - steps[0] * counts;
            } else {
                index = i;
            }
            if (index >= (int)rails) {
                index = steps[0] - index;
            }
            if (index == j) {
                indexes[k++] = i;
            }
        }
    }

    for (int i = 0; i < input_length; i++) {
        ans[indexes[i]] = ciphertext[i];
    }

    return ans;
}

int *get_step(size_t rails) {
    int *steps = malloc(sizeof(int) * (int)rails);
    steps[rails - 2] = 2;
    if (rails == 2) {
        steps[1] = 2;
    } else {
        for (int i = (int)rails - 2; i >= 0; i--) {
            steps[i-1] = steps[i] + 2;
        }
        steps[rails - 1] = steps[0];
    }
    return steps;
}

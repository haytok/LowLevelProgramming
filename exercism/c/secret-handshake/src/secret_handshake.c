#include "secret_handshake.h"

const char *handshakes[] = {"wink", "double blink", "close your eyes", "jump"};

const char **commands(size_t number) {
    const char **ans;
    int index;
    ans = malloc(sizeof(char *) * 1024);
    index = 0;
    if (number == 0) {
        ans[index] = NULL;
        return ans;
    }
    for (int i = 0; number > 0; i++) {
        int value = number % 2;
        number = number / 2;
        if (value == 0) {
            continue;
        } else if (i == 4) {
            if (index == 0) {
                ans[index] = NULL;
                return ans;
            }
            for (int j = 0; j < index / 2; j++) {
                const char *tmp;
                tmp = ans[j];
                ans[j] = ans[index - j - 1];
                ans[index - j - 1] = tmp;
            }
        } else if (value == 1) {
            ans[index++] = handshakes[i];
        }
    }
    return ans;
}

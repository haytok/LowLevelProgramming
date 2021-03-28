#include "armstrong_numbers.h"

bool is_armstrong_number(int candidate) {
    char input[256];
    sprintf(input,"%d",candidate);
    int len = strlen(input);
    int ans = 0;
    for (int i = 0; i < len; i++) {
        ans += pow((int)input[i] - 48, len);
    }
    return ans == candidate;
}

#include "hamming.h"

int compute(const char *lhs, const char *rhs) {
    if (strlen(lhs) != strlen(rhs)) {
        return -1;
    }
    int counts = 0;
    while (*lhs && *rhs) {
        if (strncmp(lhs, rhs, 1) != 0) {
            counts++;
        }
        lhs++;
        rhs++;
    }
    return counts;
}

#include "sum_of_multiples.h"

unsigned int sum(const unsigned int *factors,
                 const size_t number_of_factors, const unsigned int limit) {
    int under_ans = 0;
    int ans = 0;
    bool flag = false;
    for (int i = 0; i < (int)number_of_factors; i++) {
        if (factors[i] == 0) {
            flag = true;
        } else {
            under_ans += factors[i];
        }
    }
    if (flag) {
        return under_ans;
    }
    for (int j = 0; j < (int)limit; j++) {
        for (int k = 0; k < (int)number_of_factors; k++) {
            if (j % factors[k] == 0) {
                ans += j;
                break;
            }
        }
    }
    return ans;
}

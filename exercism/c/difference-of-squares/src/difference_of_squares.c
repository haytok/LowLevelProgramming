#include "difference_of_squares.h"

unsigned int square_of_sum(unsigned int number) {
    int ans = 0;
    for (int i = 1; i <= (int)number; i++) {
        ans += i;
    }
    return ans * ans;
}

unsigned int sum_of_squares(unsigned int number) {
    int ans = 0;
    for (int i = 1; i <= (int)number; i++) {
        ans += i * i;
    }
    return ans;
}

unsigned int difference_of_squares(unsigned int number) {
    return square_of_sum(number) - sum_of_squares(number);
}

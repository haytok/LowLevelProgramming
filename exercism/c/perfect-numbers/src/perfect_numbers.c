#include "perfect_numbers.h"

kind classify_number(int value) {
    if (value <= 0) {
        return ERROR;
    }
    int sum = 0;
    for (int i = 1; i < value; ++i) {
        if ( value % i == 0 ) {
            sum += i;
        }
    }
    if (sum == value) {
        return PERFECT_NUMBER;
    } else if (sum > value) {
        return ABUNDANT_NUMBER;
    } else if (sum < value) {
        return DEFICIENT_NUMBER;
    }
    return ERROR;
}

#include "binary_search.h"

int *binary_search(int value, int *arr, size_t length) {
    int left, right, middle;
    left = 0;
    right = length - 1;
    while (left <= right) {
        middle = (left + right) / 2;
        if (arr[middle] == value) {
            printf("middle %d:\n", middle);
            return &arr[middle];
        } else if (arr[middle] < value) {
            left = middle + 1;
        } else if (arr[middle] > value) {
            right = middle - 1;
        }
    }
    return NULL;
}

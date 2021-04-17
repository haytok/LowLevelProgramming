#include "all_your_base.h"

size_t rebase(
    int8_t digits[DIGITS_ARRAY_SIZE],
    int16_t input_base,
    int16_t output_base,
    size_t input_length
) {
    int index = 0;
    if (input_base < 0 || output_base < 2) {
        digits[index] = 0;
        return index;
    }
    int value = 0;
    for (int i = 0; i < (int)input_length; i++) {
        // printf("digits %d, pow %d\n", digits[i], (int)(input_length - i - 1));
        if (digits[i] < 0 || digits[i] >= input_base) {
            digits[index] = 0;
            return index;
        }
        value += pow(input_base, input_length - i - 1) * digits[i];
    }
    // 変換処理
    int j, b[1024];
    for (j = 0; value > 0; j++) {
        b[j] = value % (int)output_base;
        value /= (int)output_base;
    }
    // 代入処理
    while (j > 0) {
        digits[index++] = (int8_t)b[--j];
    }
    return index;
}

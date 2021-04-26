#include "crypto_square.h"

char *ciphertext(const char *input) {
    char *ans = malloc(sizeof(char) * 1024);
    if (strcmp(input, "") == 0) {
        return ans;
    }
    int length = strlen(input);
    int counts = 0;
    for (int i = 0; i < length; i++) {
        if (isalnum(input[i])) {
            ans[counts++] = tolower(input[i]);
        }
    }
    int r = 1;
    int diff = 0;
    bool flag = true;
    // r * c の値を計算する。
    while (flag) {
        for (diff = 0; diff < 2; diff++) {
            int value = r * (r + diff);
            if (value >= counts) {
                flag = false;
                break;
            }
        }
        if (flag) {
            r++;
        }
    }
    int c = r + diff;
    int write_index = 0;
    char *res = malloc(sizeof(char) * 4096);
    for (int c_index = 0; c_index < c; c_index++) {
        for (int r_index = 0; r_index < r; r_index++) {
            int read_index = r_index * c + c_index;
            // 右辺の評価式に入れる変数名を間違えてた。
            res[write_index++] = (read_index < counts) ? ans[read_index] : ' ';
        }
        if (c_index + 1 < c) {
            res[write_index++] = ' ';
        }
    }
    free(ans);
    return res;
}

// #include <stddef.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>
// #include <ctype.h>
// #include "crypto_square.h"

// static char* normalize(const char* input)
// {
//   char* normalized = calloc(strlen(input) + 1, sizeof(char));
//   char* current = normalized;

//   while(*input) {
//     if(isalnum(*input)) {
//       *current++ = tolower(*input);
//     }

//     input += 1;
//   }

//   return normalized;
// }

// char* ciphertext(const char* input)
// {
//   char* normalized = normalize(input);
//   size_t normalized_length = strlen(normalized);

//   size_t c = ceil(sqrt(normalized_length));
//   size_t r = (normalized_length + c - 1) / (c ? c : 1);

//   char* output = calloc(c * (c + 1), sizeof(char));
//   size_t offset = 0;

//   for(size_t column = 0; column < c; column++) {
//     for(size_t row = 0; row < r; row++) {
//       size_t i = row * c + column;
//       output[offset++] = (i < normalized_length) ? normalized[i] : ' ';
//     }

//     if(column + 1 < c) {
//       output[offset++] = ' ';
//     }
//   }

//   free(normalized);

//   return output;
// }

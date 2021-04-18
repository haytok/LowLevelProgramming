#include "etl.h"

// typedef struct {
//    int score;
//    const char *letters;
// } legacy_map;

// typedef struct {
//    char key;
//    int value;
// } new_map;

int compare(const void *a, const void *b) {
    return ((new_map *)a)->key - ((new_map *)b)->key;
}

int convert(const legacy_map * input, const size_t input_len,
            new_map ** output) {
    int count = 0;
    *output = malloc(sizeof(new_map) * 1024);

    for (int i = 0; i < (int)input_len; i++) {
        // 文字列の長さを計算する必要がない。
        for (int j = 0; input[i].letters[j]; j++) {
            // (*output)[インデックス] でオブジェクトに値を代入できる。
            (*output)[count].key = tolower(input[i].letters[j]);
            (*output)[count].value = input[i].score;
            count++;
        }
    }
    // void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
    qsort(*output, count, sizeof(output), compare);
    return count;
}

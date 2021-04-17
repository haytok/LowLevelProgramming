#include "palindrome_products.h"

// 愚直に計算すると、計算が莫大になるので、適当にエスケープする。
// 文字列の反転や構造体を使用したオブジェクトの作成方法や連結リストの基本を学んだ。
product_t *get_palindrome_product(int from, int to) {
    product_t *product;
    product = malloc(sizeof(product_t));
    if (from > to) {
        char *fmt = "invalid input: min is %d and max is %d";
        sprintf(product->error, fmt, from, to);
        return product;
    }
    product->largest = 0;
    product->smallest = 10000000000;
    product->factors_lg = malloc(sizeof(factor_t) * 1024);
    product->factors_sm = malloc(sizeof(factor_t) * 1024);
    int factors_lg_index, factors_sm_index;
    factors_lg_index = 0;
    factors_sm_index = 0;
    for (int i = from; i <= to; i++) {
        for (int j = i; j <= from + 100; j++) {
            // if () {
            //     goto small_end;
            // }
            char *buf, *rev_buf;
            int length, mul_value;
            buf = malloc(sizeof(char) * 1024);
            rev_buf = malloc(sizeof(char) * 1024);
            length = 0;
            mul_value = i * j;
            sprintf(buf, "%d", mul_value);
            // length = strlen(buf);
            strcpy(rev_buf, buf);
            // 文字列を反転させる処理
            rev_string(rev_buf);
            if (strcmp(buf, rev_buf) == 0) {
                if (product->smallest > mul_value) {
                    product->smallest = mul_value;
                    factors_sm_index++;
                }
            }
        }
    }
    small_end:
    if (factors_sm_index == 0 || from == to) {
        char *fmt = "no palindrome with factors in the range %d to %d";
        sprintf(product->error, fmt, from, to);
        return product;
    }
    for (int i = to; i >= from; i--) {
        for (int j = i; j >= to - 100; j--) {
            char *buf, *rev_buf;
            int length, mul_value;
            buf = malloc(sizeof(char) * 1024);
            rev_buf = malloc(sizeof(char) * 1024);
            length = 0;
            mul_value = i * j;
            sprintf(buf, "%d", mul_value);
            // length = strlen(buf);
            strcpy(rev_buf, buf);
            // 文字列を反転させる処理
            rev_string(rev_buf);
            if (strcmp(buf, rev_buf) == 0) {
                if (product->largest < mul_value) {
                    product->largest = mul_value;
                    factors_lg_index++;
                }
            }
        }
    }
    large_end:
    if (factors_sm_index == 0) {
        char *fmt = "no palindrome with factors in the range %d to %d";
        sprintf(product->error, fmt, from, to);
        return product;
    }
    //
    for (int k = 1; k <= (int)sqrt(product->largest); k++) {
        if (product->largest % k == 0) {
            // connect_factors(product, k, product->largest / k);
            factor_t *factor;
            factor = malloc(sizeof(factor_t) * 1024);
            factor->factor_a = k;
            factor->factor_b = product->largest / k;
            // 付け替え処理
            factor->next = product->factors_lg;
            product->factors_lg = factor;
        }
    }
    for (int j = 1; j <= (int)sqrt(product->smallest); j++) {
        if (product->smallest % j == 0) {
            // connect_factors(product, j, product->smallest / j);
            factor_t *factor;
            factor = malloc(sizeof(factor_t) * 1024);
            factor->factor_a = j;
            factor->factor_b = product->smallest / j;
            // 付け替え処理
            factor->next = product->factors_sm;
            product->factors_sm = factor;
        }
    }
    return product;
}


unsigned str_length(const char str[]) {
    unsigned len = 0;
    while (str[len])
        len++;
    return (len);
}

void rev_string(char str[]) {
    int i;
    int len = str_length(str);
    for (i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
}

// typedef struct factors {
//    int factor_a;
//    int factor_b;
//    struct factors *next;
// } factor_t;

// struct product {
//    int smallest;
//    int largest;
//    factor_t *factors_sm;
//    factor_t *factors_lg;
//    char error[MAXERR];
// };

// typedef struct product product_t;

void free_factor(struct factors *f) {
    if (f) {
        free_factor(f->next);
        free(f);
    }
}

void free_product(product_t * p) {
    // free_factor((struct factors *)(p->factors_lg));
    // free_factor((struct factors *)(p->factors_sm));
    // free(p);
}

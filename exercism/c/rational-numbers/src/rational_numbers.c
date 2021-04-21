#include "rational_numbers.h"

rational_t mixin_of_add_and_subtract(rational_t r1, rational_t r2, char *type) {
    // 分母
    int denominator = get_lcm(r1.denominator, r2.denominator);
    // 分子
    int numerator = 0;
    if (strcmp(type, "add") == 0) {
        numerator = r1.numerator * (denominator / r1.denominator) + r2.numerator * (denominator / r2.denominator);
    } else if (strcmp(type, "subtract") == 0) {
        numerator = r1.numerator * (denominator / r1.denominator) - r2.numerator * (denominator / r2.denominator);
    }
    if (numerator == 0) {
        denominator = 1;
    } else if (numerator % denominator == 0) {
        denominator /= numerator;
        numerator /= numerator;
    }
    return (rational_t){
        .numerator = numerator,
        .denominator = denominator,
    };
}

rational_t add(rational_t r1, rational_t r2) {
    return mixin_of_add_and_subtract(r1, r2, "add");
}

rational_t subtract(rational_t r1, rational_t r2) {
    return mixin_of_add_and_subtract(r1, r2, "subtract");
}

rational_t mixin_of_multiply_and_divide(rational_t r1, rational_t r2, char *type) {
    // 分母
    int denominator = 0;
    // 分子
    int numerator = 0;
    if (strcmp(type, "multiply") == 0) {
        denominator = r1.denominator * r2.denominator;
        numerator = r1.numerator * r2.numerator;
    } else if (strcmp(type, "divide") == 0) {
        denominator = r1.denominator * r2.numerator;
        numerator = r1.numerator * r2.denominator;
    }
    if (numerator == 0) {
        return (rational_t){
            .numerator = 0,
            .denominator = 1,
        };
    }
    int gcm = get_gcm(numerator < 0 ? numerator * (-1) : numerator, denominator);
    denominator /= gcm;
    numerator /= gcm;
    return (rational_t){
        .numerator = numerator,
        .denominator = denominator,
    };
}

rational_t multiply(rational_t r1, rational_t r2) {
    return mixin_of_multiply_and_divide(r1, r2, "multiply");
}

rational_t divide(rational_t r1, rational_t r2) {
    return mixin_of_multiply_and_divide(r1, r2, "divide");
}

int my_abs(int value) {
    return value > 0 ? value : value * (-1);
}

rational_t absolute(rational_t r) {
    r.denominator = my_abs(r.denominator);
    r.numerator = my_abs(r.numerator);
    return r;
}

double my_pow(double value, int n) {
    double ans = 1.0;
    while (n > 0) {
        ans *= (double)value;
        n--;
    }
    return ans;
}

rational_t exp_rational(rational_t r, uint16_t n) {
    r.denominator = my_pow(r.denominator, (int)n);
    r.numerator = my_pow(r.numerator, (int)n);
    return r;
}

int my_root(double value, int n) {
    for (int i = 0; i <= value; i++) {
        if (value == my_pow(i, n)) {
            return i;
        }
    }
    return -1;
}

float exp_real(uint16_t x, rational_t r) {
    bool flag = false;
    if (r.numerator < 0) {
        flag = true;
        r.numerator = r.numerator * (-1);
    }
    float numerator = my_pow(x, r.numerator);
    return flag ? 1.0 / my_root(numerator, r.denominator) : my_root(numerator, r.denominator);
}

rational_t reduce(rational_t r) {
    if (r.numerator == 0) {
        return (rational_t){
            .numerator = 0,
            .denominator = 1,
        };
    }
    bool is_negative = false;
    if (r.numerator < 0) {
        is_negative = !is_negative;
        r.numerator = r.numerator * (-1);
    }
    if (r.denominator < 0) {
        is_negative = !is_negative;
        r.denominator = r.denominator * (-1);
    }
    int gcm = get_gcm(r.numerator, r.denominator);
    r.denominator /= gcm;
    r.numerator /= gcm;
    return (rational_t){
        .numerator =  is_negative ? r.numerator  * (-1) : r.numerator,
        .denominator = r.denominator,
    };
}

int get_gcm(int x, int y) {
    int r;

    if (x == 0 || y == 0) {
        fprintf(stderr, "引数エラーです。\n");
        return 0;
    }

    // ユーグリッドの互除法
    // yで割り切れるまでループ
    while((r = x % y) != 0) {
        x = y;
        y = r;
    }
    return y;
}

int get_lcm(int a, int b) {
  int r, x, tmp;
 
  x = a * b;
 
  /* 自然数 a > b を確認・入替 */
  if (a < b){
    tmp = a;
    a = b;
    b = tmp;
  }
 
  /* ユークリッドの互除法 */
  r = a % b;
  while (r != 0){
    a = b;
    b = r;
    r = a % b;
  }
 
  return x / b;
}

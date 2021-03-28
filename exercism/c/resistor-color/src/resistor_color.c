#include "resistor_color.h"

int *colors() {
    // static がないと、以下のエラーが生じる。
    static int ans[TYPES];
    for (int i = BLACK; i < TYPES; i++) {
        ans[i] = i;
    }
    return ans;
}

// src/resistor_color.c:8:12: error: function returns address of local variable [-Werror=return-local-addr]
//      return ans;

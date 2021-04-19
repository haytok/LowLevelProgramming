#include "diamond.h"

char **make_diamond(const char letter) {
    char base = 'A';
    int diff = letter - 'A';
    int length = diff * 2 + 1;
    char **ans;
    ans = malloc(sizeof(char *) * length);
    for (int row = 0; row < length; row++) {
        ans[row] = malloc(sizeof(char *) * length);
        for (int column = 0; column < length; column++) {
            if (row == 0 || row == length - 1) {
                if (column == letter - 'A') {
                    ans[row][column] = base;
                } else {
                    ans[row][column] = ' ';
                }
            } else {
                if (column == diff || column == length - 1 - diff) {
                    ans[row][column] = base;
                } else {
                    ans[row][column] = ' ';
                }
            }
        }
        if (row >= 0 && row < letter - 'A') {
            base++;
            diff--;
        } else {
            base--;
            diff++;
        }
    }
    return ans;
}

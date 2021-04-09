#include "isogram.h"

bool is_isogram(const char phrase[]) {
    if (!phrase) {
        return false;
    }
    for (u_int i = 0; i < strlen(phrase); i++) {
        char string = tolower(phrase[i]);
        for (u_int j = 0; j < strlen(phrase); j++) {
            if (isalpha(string) && j != i && tolower(phrase[j]) == string) {
                return false;
            }
        }
    }
    return true;
}

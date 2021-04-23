#include "scrabble_score.h"

unsigned int score(const char *word) {
    int score[LENGTH] = {
        1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
    };
    int length = strlen(word);
    int ans = 0;
    for (int i = 0; i < length; i++) {
        int index = tolower(word[i]) - 'a';
        ans += score[index];
    }
    return (unsigned int)ans;
}

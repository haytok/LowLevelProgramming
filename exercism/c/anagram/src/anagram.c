#include "anagram.h"

#define LENGTH 300
#define STEP 250

void find_anagrams(char *subject, struct candidates *candidates) {
    lowcase(subject);
    // 文字列の出現回数を記録するテーブルの作成
    char base_strings[LENGTH] = {0};
    for (int h = 0; h < (int)strlen(subject); h++) {
        int index = tolower(subject[h]) - 'a';
        if (index < 0) {
            base_strings[index + STEP]++;
        }
        base_strings[index]++;
    }
    for (int i = 0; i < (int)candidates->count; i++) {
        lowcase(candidates->candidate[i].word);
        // 同じ文字列の際に弾く処理
        if (strcmp(subject, candidates->candidate[i].word) == 0) {
            candidates->candidate[i].is_anagram = NOT_ANAGRAM;
            continue;
        }
        char strings[LENGTH] = {0};
        int length = strlen(candidates->candidate[i].word);
        for (int j = 0; j < length; j++) {
            int index = tolower(candidates->candidate[i].word[j]) - 'a';
            if (index < 0) {
                base_strings[index + STEP]++;
            }
            strings[index]++;
        }
        // 双方のテーブルを比較して、アナグラムかどうかを確認する。
        int k;
        for (k = 0; k < LENGTH; k++) {
            if (base_strings[k] != strings[k]) {
                candidates->candidate[i].is_anagram = NOT_ANAGRAM;
                break;
            }
        }
        if (k == LENGTH) {
            candidates->candidate[i].is_anagram = IS_ANAGRAM;
        }
    }
}

void lowcase(char *strings) {
    char *p;
    for (p = strings; *p; p++) {
        *p = (char)tolower((int)*p);
    }
}

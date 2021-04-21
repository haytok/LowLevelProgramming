#include "anagram.h"

// enum anagram_status {
//    UNCHECKED = -1,
//    NOT_ANAGRAM,
//    IS_ANAGRAM
// };

// struct candidate {
//    enum anagram_status is_anagram;
//    const char *word;
// };

// struct candidates {
//    struct candidate *candidate;
//    size_t count;
// };

// typedef struct {
//    char key;
//    int counts;
// } element_t;

/**
 * @description - determines if any of the words in candidate are anagrams
 *                for subject. Contents of candidate structures may be modified.
 */
void find_anagrams(char *subject, struct candidates *candidates) {
    printf("subject is %s\n", subject);
    lowcase(subject);
    for (int i = 0; i < (int)candidates->count; i++) {
        lowcase(candidates->candidate[i].word);
        // 同じ文字列の際に弾く処理
        if (strcmp(subject, candidates->candidate[i].word) == 0) {
            candidates->candidate[i].is_anagram = NOT_ANAGRAM;
            continue;
        }
        // 文字列の出現回数を記録するテーブルの作成
        char base_strings[LENGTH] = {0};
        for (int h = 0; h < (int)strlen(subject); h++) {
            printf("%d\n", subject[h] - 'a');
            int index = tolower(subject[h]) - 'a';
            base_strings[index]++;
        }
        printf("In find_anagrams, %s\n", candidates->candidate[i].word);
        int char_kinds = 0;
        char strings[LENGTH] = {0};
        int length = strlen(candidates->candidate[i].word);
        for (int j = 0; j < length; j++) {
            int index = tolower(candidates->candidate[i].word[j]) - 'a';
            strings[index]++;
        }
        printf("base_strings ->");
        for (int a = 0; a < LENGTH; a++) {
            printf("%d,", base_strings[a]);
        }
        printf("\n");
        printf("strings      ->");
        for (int a = 0; a < LENGTH; a++) {
            printf("%d,", strings[a]);
        }
        printf("\n");
        int k;
        for (k = 0; k < LENGTH; k++) {
            if (strings[k] == 1) {
                printf("base_string %c, string %c\n", k + 'a', k + 'a');
            }
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

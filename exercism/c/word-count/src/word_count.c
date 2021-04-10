#include "word_count.h"

// word_count_word_t actual_solution[MAX_WORDS];
int count_words(const char *sentence, word_count_word_t * words) {
    int index;
    int counts;
    char *head, *start;
    index = 0;
    counts = 0;
    bool flag = false;

    // printf("-----sentence %s\n", sentence);
    head = malloc(sizeof(char *) * 1024);
    memcpy(head, sentence, 1024);
    start = malloc(sizeof(char *) * 1024);
    start = head;

    while (true) {
        // 1 word or 最後の文字列のケース
        if (memcmp(head, "\0", 1) == 0) {
            char *buf;
            buf = malloc(sizeof(char *) * 1024);
            strncpy(buf, start, head - start);
            lowcase(buf);
            // printf("%s %d\n", buf, strcmp(buf, "") == 0);
            if (strcmp(buf, "") == 0) {
                break;
            }
            // 関数で切り出せそう
            int i;
            if ((i = is_exit(words, buf)) >= 0) {
                // words[i].count をインクリメント
                words[i].count++;
            } else {
                strcpy(words[index].text, buf);
                words[index++].count = 1;
            }
            break;
        }
        if (isdigit(*head) != 0) {
            // printf("isdigi %c\n", *head);
            char *buf;
            buf = malloc(sizeof(char *) * 1024);
            strncpy(buf, start, 1);
            lowcase(buf);
            // 関数で切り出せそう
            int i;
            if ((i = is_exit(words, buf)) >= 0) {
                // words[i].count をインクリメント
                words[i].count++;
            } else {
                strcpy(words[index].text, buf);
                words[index++].count = 1;
            }
            head++;
            start = head;
        } else if (*head == '\'') {
            if (flag) {
                char *buf;
                buf = malloc(sizeof(char *) * 1024);
                strncpy(buf, start, head - start);
                lowcase(buf);
                // printf("this :%s:%c:%d:%d:\n", buf, *head, isalpha(*head), start == head);
                // 関数で切り出せそう
                int i;
                if ((i = is_exit(words, buf)) >= 0) {
                    // words[i].count をインクリメント
                    words[i].count++;
                } else {
                    strcpy(words[index].text, buf);
                    words[index++].count = 1;
                }
                head++;
                start = head;
                continue;
            }
            if (start == head) {
                head++;
                start = head;
                flag = true;
                continue;
            }
            head++;
            continue;
        } else if (isalpha(*head) == 0) {
            if (start == head) {
                head++;
                start = head;
                continue;
            }
            // 記号
            char *buf;
            buf = malloc(sizeof(char *) * 1024);
            strncpy(buf, start, head - start);
            lowcase(buf);
            // printf("this :%s:%c:%d:%d:\n", buf, *head, isalpha(*head), start == head);
            // 関数で切り出せそう
            int i;
            if ((i = is_exit(words, buf)) >= 0) {
                // words[i].count をインクリメント
                words[i].count++;
            } else {
                strcpy(words[index].text, buf);
                words[index++].count = 1;
            }
            head++;
            start = head;
        } else {
            // アルファベット
            head++;
        }
    }

    // start = head;
    // printf("start %s\n", start);

    // while (true) {
    //     if (memcmp(head, "\0", 1) == 0) {
    //         char *buf;
    //         buf = malloc(sizeof(char *) * 1024);
    //         strncpy(buf, start, head - start);
    //         bool flag = false;
    //         for (int i = 0; i < MAX_WORDS; i++) {
    //             if (strlen(words[i].text) == 0) {
    //                 break;
    //             }
    //             if (strcmp(words[i].text, buf) == 0) {
    //                 flag = true;
    //                 words[i].count++;
    //             }
    //         }
    //         printf("buf: %sbool: %d\n", buf, flag);
    //         // 登録が完了していないケース
    //         if (!flag) {
    //             for (int i = 0; i < MAX_WORDS; i++) {
    //                 if (strlen(words[i].text) == 0) {
    //                     strcpy(words[i].text, buf);
    //                     words[i].count++;
    //                     break;
    //                 }
    //             }
    //         }

    //         start = head;
    //         index++;
    
    //         // strncpy(words[index].text, start, head - start);
    //         // printf("%s\n", words[index].text);
    //         // words[index].count += 1;
    //         // start = head;
    //         // index++;
    //     } else if (
    //         memcmp(head, " ", 1) == 0
    //         || *head == '\n'
    //         // || memcmp(head, "\n", 1) == 0
    //         || memcmp(head, "\t", 1) == 0
    //         // || memcmp(head, ",", 1) == 0
    //         || *head == ','
    //     ) {
    //         head++;
    //         if (*head == '\n') {
    //             head++;
    //         }

    //         char *buf;
    //         buf = malloc(sizeof(char *) * 1024);
    //         strncpy(buf, start, head - start - 1);
    //         bool flag = false;
    //         for (int i = 0; i < MAX_WORDS; i++) {
    //             if (strlen(words[i].text) == 0) {
    //                 break;
    //             }
    //             if (strcmp(words[i].text, buf) == 0) {
    //                 flag = true;
    //                 words[i].count++;
    //             }
    //         }
    //         printf("buf: %sbool: %d\n", buf, flag);
    //         // 登録が完了していないケース
    //         if (!flag) {
    //             for (int i = 0; i < MAX_WORDS; i++) {
    //                 if (strlen(words[i].text) == 0) {
    //                     strcpy(words[i].text, buf);
    //                     words[i].count++;
    //                     break;
    //                 }
    //             }
    //         }

    //         start = head;
    //         index++;
            
    //         // strncpy(words[index].text, start, head - start);
    //         // printf("%s\n", words[index].text);
    //         // words[index].count += 1;
    //         // start = head;
    //         // index++;
    //     }
    //     // 一文字のケースのときに走る処理
    //     if (memcmp(head, "\0", 1) == 0) {
    //         break;
    //     }
    //     head++;
    // }

    // printf("-----final-----\n");

    for (int i = 0; i < MAX_WORDS; i++) {
        if (strlen(words[i].text)) {
            counts += 1;
        } else {
            break;
        }
    }

    for (int i = 0; i < MAX_WORDS; i++) {
        if (strlen(words[i].text)) {
            // printf("In for :%s:%d:\n", words[i].text, words[i].count);
        } else {
            break;
        }
    }

    // 1 word の時
    // strcpy(words[index].text, sentence);
    // words[index].count += 1;
    // counts += 1;

    // printf("-----counts : %d-----\n", counts);
    return counts;
}

int is_exit(word_count_word_t *words, char *buf) {
    for (int i = 0; i < MAX_WORDS; i++) {
        if (strlen(words[i].text) == 0) {
            return -1;
        }
        if (strcmp(words[i].text, buf) == 0) {
            return i;
        }
    }
    return -1;
}

void lowcase(char *actual) {
    char *p;
    for (p = actual; *p; p++) {
        *p = (char)tolower((int)*p);
    }
}

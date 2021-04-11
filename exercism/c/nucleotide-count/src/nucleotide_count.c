#include "nucleotide_count.h"

char *count(const char *dna_strand) {
    char *buf;
    buf = malloc(sizeof(char *) * 1024);
    char *fmt = "A:%d C:%d G:%d T:%d";

    if (strcmp(dna_strand, "") == 0) {
        sprintf(buf, fmt, 0, 0, 0, 0);
    } else {
        nucleotide_t counts[COUNTS] = {0};
        char *head;
        head = malloc(sizeof(char *) * 1024);
        memcpy(head, dna_strand, 1024);

        char *p;
        p  = malloc(sizeof(char *) * 1024);
        for (p = head; *p; p++) {
            if (*p == 'A') {
                counts[A]++;
            } else if (*p == 'T') {
                counts[T]++;
            } else if (*p == 'G') {
                counts[G]++;
            } else if (*p == 'C') {
                counts[C]++;
            } else {
                // 空文字列の生成
                memset(buf, '\0', 1);
                return buf;
                // 以下の実装でも問題ない。
                // char *res = malloc(1);
                // res[0] = '\0';
                // return res;
            }
        }
        sprintf(buf, fmt,  counts[A],  counts[C],  counts[G],  counts[T]);
    }
 
    return buf;
}

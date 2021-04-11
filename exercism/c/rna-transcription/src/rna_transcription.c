#include "rna_transcription.h"

// 入力として与えられる dna をmemcpy する。
// コピーした先の値を一つずつ見ていき、直に書き換えていく。
char *to_rna(const char *dna) {
    char *rna;
    rna = malloc(sizeof(char *) * 1024);
    memcpy(rna, dna, 1024);

    char *p;
    p  = malloc(sizeof(char *) * 1024);
    for (p = rna; *p; p++) {
        *p = (char)toupper((int)*p);
        if (*p == 'A') {
            *p = 'U';
        } else if (*p == 'T') {
            *p = 'A';
        } else if (*p == 'G') {
            *p = 'C';
        } else if (*p == 'C') {
            *p = 'G';
        }
    }
    return rna;
}

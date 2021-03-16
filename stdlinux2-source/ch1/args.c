#include <stdio.h>
#include <stdlib.h>

// pointer を利用した書き方
int main(int argc, char **argv) {
    while(*argv) {
        puts(*argv++);
    }
    exit(0);
}

// よくやる書き方
// int main(int argc, char **argv) {
//     printf("argc=%d", argc);
//     for (int i = 0; i < argc; i++) {
//         printf("argv[%d]=%s", i, argv[i]);
//     }
//     exit(0);
// }

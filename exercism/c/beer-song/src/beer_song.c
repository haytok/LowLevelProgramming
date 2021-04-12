#include "beer_song.h"

void recite(unsigned int start_bottles, unsigned int take_down, char *buffer) {
    printf("--------\n");
    char *res = malloc(sizeof(char *) * 1024);
    printf("res %s\n", res);
    for (int i = take_down; i > 0; i--) {
        printf("i: %d\n", i);
        char buf1[1024], buf2[1024];
        if (start_bottles == 0) {
            strcpy(buf1, "No more bottles of beer on the wall, no more bottles of beer.\n");
        } else if (start_bottles == 1) {
            sprintf(buf1, "%d bottle of beer on the wall, %d bottle of beer.\n", start_bottles, start_bottles);
        } else {
            sprintf(buf1, "%d bottles of beer on the wall, %d bottles of beer.\n", start_bottles, start_bottles);
        }
        start_bottles--;
        printf("start_bottles. %d\n", start_bottles);
        if ((int)start_bottles == -1) {
            strcpy(buf2, "Go to the store and buy some more, 99 bottles of beer on the wall.\n");
        } else if (start_bottles == 0) {
            strcpy(buf2, "Take it down and pass it around, no more bottles of beer on the wall.\n");
        } else if (start_bottles == 1) {
            sprintf(buf2, "Take one down and pass it around, %d bottle of beer on the wall.\n", start_bottles);
        } else {
            sprintf(buf2, "Take one down and pass it around, %d bottles of beer on the wall.\n", start_bottles);
        }
        strcat(res, strcat(buf1, buf2));
        if (i != 1) {
            strcat(res, "\n");
        }
    }
    memcpy(buffer, res, 1024);
    printf("--------\n");
    memset(res, '\0', 1024);
    free(res);
}

// この解答はナイス
// char * convert(char *buffer, size_t blen, int num)
// {
// 	size_t b;
// 	b  = snprintf(buffer, blen, "%s%s%s",
// 		 num % 3 == 0 ? "Pling" : "",
// 		 num % 5 == 0 ? "Plang" : "",
// 		 num % 7 == 0 ? "Plong" : "");
// 	if(b <= 0)
// 		snprintf(buffer, blen, "%d", num);
// 	return buffer;
// }

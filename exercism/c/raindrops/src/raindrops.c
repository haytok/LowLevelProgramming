#include "raindrops.h"

char *convert(char result[], int drops) {
    if (drops % 105 == 0) {
        strcat(result, "PlingPlangPlong");
    } else if (drops % 35 == 0) {
        strcat(result, "PlangPlong");
    } else if (drops % 21 == 0) {
        strcat(result, "PlingPlong");
    } else if (drops % 15 == 0) {
        strcat(result, "PlingPlang");
    } else if (drops % 7 == 0) {
        strcat(result, "Plong");
    } else if (drops % 5 == 0) {
        strcat(result, "Plang");
    } else if (drops % 3 == 0) {
        strcat(result, "Pling");
    } else {
        sprintf(result, "%d", drops);
    }
    // memset(res, '\0', 1024);
    return result;
}

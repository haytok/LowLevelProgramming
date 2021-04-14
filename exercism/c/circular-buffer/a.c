#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>

int main() {
    int *buffer = malloc(sizeof(int) * 2);
    for (int i = 0; i < 2; i++) {
        printf("%d\n", i);
        *buffer = i;
        // buffer++;
    }
    for (int index = 0; index < 2; index++) {
        printf("value %d\n", buffer[index]);
    }
    buffer++;
    buffer++;
    printf("%d\n", *buffer);
}

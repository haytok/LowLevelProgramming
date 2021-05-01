#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *encode(char *text, size_t rails);
char *decode(char *ciphertext, size_t rails);
int *get_step(size_t rails);

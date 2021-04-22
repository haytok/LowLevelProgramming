#ifndef ATBASH_CIPHER_H
#define ATBASH_CIPHER_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>

#define LENGTH 26

char *atbash_encode(char *input);
char *atbash_decode(const char *input);
void lowcase(char *method);
int get_index(int value);

#endif

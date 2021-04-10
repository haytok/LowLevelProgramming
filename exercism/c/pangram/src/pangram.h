#ifndef PANGRAM_H
#define PANGRAM_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_COUNTS 26

bool is_pangram(const char *sentence);
void lowcase(char *actual);

#endif

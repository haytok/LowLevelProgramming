#ifndef PIG_LATIN_H
#define PIG_LATIN_H

#include "pig_latin.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

char *translate(const char *phrase);
char *translate_word(const char *phrase);
bool is_vowel(char string);

#endif

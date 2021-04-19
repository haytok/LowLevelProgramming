#ifndef LUHN_H
#define LUHN_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>

bool luhn(const char *num);
unsigned str_length(const char str[]);
void rev_string(char str[]);

#endif

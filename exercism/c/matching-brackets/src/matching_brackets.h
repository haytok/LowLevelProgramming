#ifndef MATCHING_BRACKETS_H
#define MATCHING_BRACKETS_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>

bool is_paired(const char *input);
int get_value(int c);
int get_pair(int value);

#endif

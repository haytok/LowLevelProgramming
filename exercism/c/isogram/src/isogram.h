#ifndef ISOGRAM_H
#define ISOGRAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef unsigned int u_int;

bool is_isogram(const char phrase[]);
bool is_exist(const char string, char d[255]);

#endif

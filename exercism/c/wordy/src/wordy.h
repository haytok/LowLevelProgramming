#ifndef WORDY_H
#define WORDY_H

#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

bool answer(const char *question, int *result);
bool startswith(char *p, char *q);
char *starts_with_reserved(char *string);
void cal_value(int *ans, char *cal, int value);

#endif

#ifndef SAY_H
#define SAY_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <math.h>

#define ONE_DIGIT_LENGTH 10
#define TWO_DIGIT_LENGTH 10

int say(int64_t input, char **ans);

#endif

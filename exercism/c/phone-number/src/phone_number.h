#ifndef PHONE_NUMBER_H
#define PHONE_NUMBER_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>

char *phone_number_clean(const char *input);

#endif

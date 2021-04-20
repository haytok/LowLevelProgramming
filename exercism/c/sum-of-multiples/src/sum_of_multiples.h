#ifndef SUM_OF_MULTIPLES_H
#define SUM_OF_MULTIPLES_H

#define LENGTH 32

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>

unsigned int sum(const unsigned int *factors,
                 const size_t number_of_factors, const unsigned int limit);

#endif

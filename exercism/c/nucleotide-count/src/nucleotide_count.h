#ifndef _NUCLEOTIDE_COUNT_H
#define _NUCLEOTIDE_COUNT_H

#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum nucleotide {
   A,
   C,
   G,
   T,
   COUNTS,
} nucleotide_t;

char *count(const char *dna_strand);

#endif

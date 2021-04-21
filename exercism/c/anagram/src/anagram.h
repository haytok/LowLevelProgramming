#ifndef ANAGRAM_H
#define ANAGRAM_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>

#define MAX_STR_LEN 20

enum anagram_status {
   UNCHECKED = -1,
   NOT_ANAGRAM,
   IS_ANAGRAM
};

struct candidate {
   enum anagram_status is_anagram;
   char *word;
};

struct candidates {
   struct candidate *candidate;
   size_t count;
};

typedef struct {
   char key;
   int counts;
} element_t;

/**
 * @description - determines if any of the words in candidate are anagrams
 *                for subject. Contents of candidate structures may be modified.
 */
void find_anagrams(char *subject, struct candidates *candidates);
void lowcase(char *strings);

#endif

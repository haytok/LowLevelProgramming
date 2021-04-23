#ifndef SUBLIST_H
#define SUBLIST_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>

typedef enum {
   EQUAL,
   UNEQUAL,
   SUBLIST,
   SUPERLIST
} comparison_result_t;

comparison_result_t check_lists(int *list_to_compare, int *base_list,
                                size_t list_to_compare_element_count,
                                size_t base_list_element_count);
bool is_exist_in_array(int *compare, int *base, int end);

#endif

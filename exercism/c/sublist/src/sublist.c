#include "sublist.h"

#define ARRAY_COUNT(array) (int)(sizeof(array) / sizeof(array[0]))

comparison_result_t check_lists(int *list_to_compare, int *base_list,
                                size_t list_to_compare_element_count,
                                size_t base_list_element_count) {
    if (list_to_compare_element_count == base_list_element_count) {
        if (list_to_compare_element_count == 0 && base_list_element_count == 0) {
            return EQUAL;
        }

        for (int i = 0; i < (int)list_to_compare_element_count; i++) {
            if (list_to_compare[i] != base_list[i]) {
                return UNEQUAL;
            }
        }
        return EQUAL;
    } else if (list_to_compare_element_count < base_list_element_count) {
        if (list_to_compare_element_count == 0) {
            return SUBLIST;
        }

        int end = base_list_element_count - list_to_compare_element_count + 1;
        return is_exist_in_array(list_to_compare, base_list, end) ? SUBLIST : UNEQUAL;
    } else if (list_to_compare_element_count > base_list_element_count) {
        if (base_list_element_count == 0) {
            return SUPERLIST;
        }

        int end = list_to_compare_element_count - base_list_element_count + 1;
        return is_exist_in_array(base_list, list_to_compare, end) ? SUPERLIST : UNEQUAL;
    }
    return UNEQUAL;
}

bool is_exist_in_array(int *compare, int *base, int end) {
    for (int i = 0; i < end; i++) {
        int j;
        bool flag = true;
        for (j = 0; j < ARRAY_COUNT(compare); j++) {
            if (compare[j] != base[i + j]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            return true;
        }
    }
    return false;
}

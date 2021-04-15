#include "list_ops.h"

// constructs a new list
list_t *new_list(size_t length, list_element_t elements[]) {
    list_t *list;
    list = malloc(sizeof(list_t));
    list->length = length;
    for (int i = 0; i < (int)length; i++) {
        list->elements[i] = elements[i];
    }
    return list;
}

// append entries to a list and return the new list
list_t *append_list(list_t * list1, list_t * list2) {
    list_t *list;
    list = malloc(sizeof(list_t));
    list->length = list1->length + list2->length;
    for (int i = 0; i < (int)list1->length; i++) {
        list->elements[i] = list1->elements[i];
    }
    for (int j = (int)list1->length; j < (int)list->length; j++) {
        int index = j - (int)list1->length;
        list_element_t value = list2->elements[index];
        list->elements[j] = value;// 10;  // list2->elements[j - (int)list1->length];
    }
    return list;
}

// filter list returning only values that satisfy the filter function
list_t *filter_list(list_t * list, bool(*filter) (list_element_t)) {
    list_t *list1;
    list1 = malloc(sizeof(list_t));
    list1->length = 0;
    for (int i = 0; i < (int)list->length; i++) {
        if (filter(list->elements[i])) {
            list1->elements[list1->length++] = list->elements[i];
        }
    }
    return list1;
}

// returns the length of the list
size_t length_list(list_t * list) {
    return list->length;
}

// return a list of elements whose values equal the list value transformed by
// the mapping function
list_t *map_list(list_t * list, list_element_t(*map) (list_element_t)) {
    list_t *list1;
    list1 = malloc(sizeof(list_t));
    list1->length = 0;
    for (int i = 0; i < (int)list->length; i++) {
        list1->elements[list1->length++] = map(list->elements[i]);
    }
    return list1;
}

// folds (reduces) the given list from the left with a function
list_element_t foldl_list(list_t * list, list_element_t initial,
                          list_element_t(*foldl) (list_element_t,
                                                  list_element_t)) {
    for (int i = 0; i < (int)list->length; i++) {
        initial = foldl(list->elements[i], initial);
    }
    return initial;
}

// folds (reduces) the given list from the right with a function
list_element_t foldr_list(list_t * list, list_element_t initial,
                          list_element_t(*foldr) (list_element_t,
                                                  list_element_t)) {
    list_t *l = reverse_list(list);
    return foldl_list(l, initial, foldr);
}

// reverse the elements of the list
list_t *reverse_list(list_t * list) {
    list_t *list1;
    list1 = malloc(sizeof(list_t));
    list1->length = 0;
    for (int i = (int)list->length - 1; i >= 0; i--) {
        list1->elements[list1->length++] = list->elements[i];
    }
    return list1;
}

// destroy the entire list
// list will be a dangling pointer after calling this method on it
void delete_list(list_t * list) {
    free(list);
}

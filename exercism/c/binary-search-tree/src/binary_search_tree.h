#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node node_t;

struct node {
   node_t *right;
   node_t *left;
   int data;
};

node_t *build_tree(int *tree_data, size_t tree_data_len);
void free_tree(node_t * tree);
int *sorted_data(node_t * tree);
void add_left_node(node_t *target_node, int data);
void add_right_node(node_t *target_node, int data);
int *get_sort_data(int *data, int *index, node_t *n);
int *append(int *array, int *index, int element);

#endif

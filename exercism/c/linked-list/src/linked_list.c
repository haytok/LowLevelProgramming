#include "linked_list.h"

struct list_node {
   struct list_node *prev, *next;
   ll_data_t data;
};

struct list {
   struct list_node *first, *last;
};

// typedef int ll_data_t;
// struct list;

// constructs a new (empty) list
struct list *list_create(void) {
   struct list *l;
   l = malloc(sizeof(struct list));
   l->first = NULL;
   l->last = NULL;
   return l;
}

// checks if the list is empty
bool list_is_empty(const struct list *list) {
   return (list->first == NULL && list->last == NULL) ? true : false;
}

// inserts item at back of list
bool list_push(struct list *list, ll_data_t item_data) {
   struct list_node *node;
   node = malloc(sizeof(struct list_node));
   node->data = item_data;
   if (list_is_empty(list)) {
      node->prev = NULL;
      node->next = NULL;
      list->first = node;
      list->last = node;
   } else {
      node->prev = list->last;
      node->next = NULL;
      list->last->next = node;
      list->last = node;
   }
   return true;
}

// removes item from back of list
ll_data_t list_pop(struct list *list) {
   ll_data_t value = list->last->data;
   if (list->first == list->last) {
      list->first = NULL;
      list->last = NULL;
   } else {
      list->last = list->last->prev;
      list->last->next = NULL;
   }
   return value;
}

// inserts item at front of list
bool list_unshift(struct list *list, ll_data_t item_data) {
   struct list_node *node;
   node = malloc(sizeof(struct list_node));
   node->data = item_data;
   if (list_is_empty(list)) {
      node->prev = NULL;
      node->next = NULL;
      list->first = node;
      list->last = node;
   } else {
      node->prev = NULL;
      node->next = list->first;
      list->first->prev = node;
      list->first = node;
   }
   return true;
}

// removes item from front of list
ll_data_t list_shift(struct list *list) {
   struct list_node *node;
   node = malloc(sizeof(struct list_node));
   node = list->first;
   if (list->first == list->last) {
      list->first = NULL;
      list->last = NULL;
   } else {
      list->first->next->prev = NULL;
      list->first = list->first->next;
   }
   return node->data;
}

// destroys the entire list
// list will be a dangling pointer after calling this method on it
void list_destroy(struct list *list) {
   free(list);
}

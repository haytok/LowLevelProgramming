#include "binary_search_tree.h"

// typedef struct node node_t;

// struct node {
//    node_t *right;
//    node_t *left;
//    int data;
// };

node_t *build_tree(int *tree_data, size_t tree_data_len) {
    node_t *n = malloc(sizeof(node_t) * 1);
    n->data = tree_data[0];

    // 長さが 2 以上の tree_data が入力された時の処理
    if (tree_data_len > 1) {
        for (int i = 1; i < (int)tree_data_len; i++) {
            // printf("=========\n");
            // printf("value %d\n", tree_data[i]);
            if (n->data >= tree_data[i]) {
                add_left_node(n, tree_data[i]);
            } else {
                add_right_node(n, tree_data[i]);
            }
        }
    }
    return n;
}

void add_left_node(node_t *target_node, int data) {
    // printf("In add_left_node, data %d, target_node->data %d\n", data, target_node->data);
    if (target_node->left == NULL) {
        node_t *l = malloc(sizeof(node_t) * 1);
        l->data = data;
        target_node->left = l;
    } else {
        // left node に追加
        if (target_node->left->data >= data) {
            add_left_node(target_node->left, data); // 第一引数が間違えていた。
        } else {
            add_right_node(target_node->left, data); // 第一引数が間違えていた。
        }
    }
}

void add_right_node(node_t *target_node, int data) {
    // printf("In add_right_node, data %d\n", data);
    if (target_node->right == NULL) {
        node_t *r = malloc(sizeof(node_t) * 1);
        r->data = data;
        target_node->right = r;
    } else {
        // left node に追加
        // printf("In add_right_node else, data %d, target_node->right->data %d\n", data, target_node->right->data);
        if (target_node->right->data < data) {
            add_right_node(target_node->right, data); // 第一引数が間違えていた。どっちの Node を起点に生やすか。
        } else {
            add_left_node(target_node->right, data); // 第一引数が間違えていた。
        }
    }
}

void free_tree(node_t * tree) {
    if (tree == NULL) {
        return;
    }
    // free_tree(tree->left);
    // free_tree(tree->right);
    // free(tree);
}

int *sorted_data(node_t * tree) {
    int index = 0;

    return get_sort_data(NULL, &index, tree);
}

int *append(int *array, int *index, int element) {
    if (array == NULL) {
        array = malloc(sizeof(int) * 1);
        // 参照渡しの変数をインクリメントする際は、以下の記述をする必要がある。
        // (*index)++
        array[(*index)++] = element;
    } else {
        array = realloc(array, sizeof(int) * (*index + 1));
        array[(*index)++] = element;
    }
    return array;
}

int *get_sort_data(int *data, int *index, node_t *n) {
    if (n == NULL) {
        return data;
    }

    if (n->left != NULL) {
        data = get_sort_data(data, index, n->left);
    }

    data = append(data, index, n->data);


    if (n->right != NULL) {
        data = get_sort_data(data, index, n->right);
    }

    return data;
}

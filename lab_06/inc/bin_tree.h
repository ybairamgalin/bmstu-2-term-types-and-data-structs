#ifndef _BIN_TREE_H_
#define _BIN_TREE_H_

#include "data.h"

struct bin_tree {
    data_t *data;
    int height;
    struct bin_tree *left;
    struct bin_tree *right;
};

typedef struct bin_tree bin_tree_t;

bin_tree_t *bin_tree_insert(bin_tree_t *tree, data_t *data);
bin_tree_t *bin_tree_insert_dn_balance(bin_tree_t *tree, data_t *data);
void bin_tree_show_all_children(bin_tree_t *tree);
data_t *bin_tree_find(bin_tree_t *tree, const char *key);
bin_tree_t *bin_tree_remove(bin_tree_t *tree, const char *restrict key);

int bin_tree_height(bin_tree_t *tree);

void bin_tree_grapfviz(bin_tree_t *tree);

#endif

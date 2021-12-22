#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include "bin_tree.h"

int total_cmp = 0;

static int my_strcmp(const char *restrict first, const char *restrict second)
{
    total_cmp++;
    return strcmp(first, second);
}

bin_tree_t *bin_cree_create(data_t *data)
{
    bin_tree_t *new_tree = malloc(sizeof(bin_tree_t));

    if (new_tree == NULL)
        return NULL;

    new_tree->right = NULL;
    new_tree->left = NULL;
    new_tree->height = 1;
    new_tree->data = data;

    return new_tree;
}

int bin_tree_height(bin_tree_t *tree)
{
    if (!tree)
        return 0;

    return tree->height;
}

static void fix_height(bin_tree_t *tree)
{
    int left = tree->left ? (tree->left->height) : 0;
    int right = tree->right ? (tree->right->height) : 0;

    tree->height = (left > right ? left : right) + 1;
}

static bin_tree_t *rotate_left(bin_tree_t *tree)
{
    bin_tree_t *root = tree->right;
    tree->right = root->left;
    root->left = tree;


    fix_height(root->left);
    fix_height(root);

    return root;
}

static bin_tree_t *rotate_right(bin_tree_t *tree)
{
    bin_tree_t *root = tree->left;
    tree->left = root->right;
    root->right = tree;

    fix_height(root->right);
    fix_height(root);

    return root;
}

static bin_tree_t *bin_tree_balance(bin_tree_t *tree)
{
    if (!tree)
        return NULL;

    fix_height(tree);

    if (bin_tree_height(tree->right) - bin_tree_height(tree->left) >= 2)
    {
        if (bin_tree_height(tree->right->left) - bin_tree_height(tree->right->right) > 0)
            tree->right = rotate_right(tree->right);

        return rotate_left(tree);
    }

    if (bin_tree_height(tree->left) - bin_tree_height(tree->right) >= 2)
    {
        if (bin_tree_height(tree->left->right) - bin_tree_height(tree->left->left) > 0)
            tree->left = rotate_left(tree->left);

        return rotate_right(tree);
    }

    return tree;
}

bin_tree_t *bin_tree_insert(bin_tree_t *tree, data_t *data)
{
    if (tree == NULL)
        return bin_cree_create(data);

    if (strcmp(data->word, tree->data->word) < 0)
        tree->left = bin_tree_insert(tree->left, data);
    else
        tree->right = bin_tree_insert(tree->right, data);

    return bin_tree_balance(tree);
}

bin_tree_t *bin_tree_insert_dn_balance(bin_tree_t *tree, data_t *data)
{
    if (tree == NULL)
        return bin_cree_create(data);

    if (strcmp(data->word, tree->data->word) < 0)
        tree->left = bin_tree_insert_dn_balance(tree->left, data);
    else
        tree->right = bin_tree_insert_dn_balance(tree->right, data);

    return tree;
}

void bin_tree_show_all_children(bin_tree_t *tree)
{
    if (!tree)
        return;

    printf("Node id = %d, word = %s\n", tree->data->id, tree->data->word);

    if (tree->left)
        bin_tree_show_all_children(tree->left);

    if (tree->right)
        bin_tree_show_all_children(tree->right);
}

data_t *bin_tree_find(bin_tree_t *tree, const char *key)
{
    if (!tree)
        return NULL;

    int cmp = my_strcmp(key, tree->data->word);

    if (cmp == 0)
        return tree->data;

    if (cmp > 0)
        return bin_tree_find(tree->right, key);

    return bin_tree_find(tree->left, key);
}

static bin_tree_t *find_min(bin_tree_t *tree)
{
    return (tree->left) ? find_min(tree->left) : tree;
}

static bin_tree_t *removemin(bin_tree_t *tree)
{
    if (!tree->left) // if no nodes are connected on the left, than 'tree' is min node
        return tree->right;

    tree->left = removemin(tree->left);

    return bin_tree_balance(tree);
}

bin_tree_t *bin_tree_remove(bin_tree_t *tree, const char *restrict key)
{
    if (!tree)
        return NULL;

    int cmp = strcmp(key, tree->data->word);

    if (cmp > 0)
    {
        tree->right = bin_tree_remove(tree->right, key);
        return bin_tree_balance(tree);
    }

    if (cmp < 0)
    {
        tree->left = bin_tree_remove(tree->left, key);
        return bin_tree_balance(tree);
    }

    if (!tree->right)
        return tree->left;

    bin_tree_t *min = find_min(tree->right);
    min->right = removemin(tree->right);
    min->left = tree->left;
    free(tree);

    return bin_tree_balance(min);
}

static void generate_graphviz(FILE *file, bin_tree_t *tree)
{
    if (!tree)
        return;

    fprintf(file, "\t%d [label=\"%s, %d\"];\n", tree->data->id, tree->data->word, tree->height);

    if (tree->left)
    {
        fprintf(file, "\t%d -> %d;\n", tree->data->id, tree->left->data->id);
        generate_graphviz(file, tree->left);
    }

    if (tree->right)
    {
        fprintf(file, "\t%d -> %d;\n", tree->data->id, tree->right->data->id);
        generate_graphviz(file, tree->right);
    }
}

void bin_tree_grapfviz(bin_tree_t *tree)
{
    FILE *graphviz_file = fopen("../lab_06/data/tree.gv.txt", "w");

    if (graphviz_file == NULL)
    {
        fprintf(stderr, "Couldn't open graphviz file\n");
        return;
    }

    fprintf(graphviz_file, "digraph BST {\n");
    generate_graphviz(graphviz_file, tree);
    fprintf(graphviz_file, "}\n");
    fclose(graphviz_file);

    system("dot -Tpng ../lab_06/data/tree.gv.txt > ../lab_06/data/out.png");
    system("open ../lab_06/data/out.png");
}

#ifndef __SPARSE_MATRIX_H__
#define __SPARSE_MATRIX_H__

#include <stdlib.h>

#define MEM_ERR 2;
#define INPUT_ERR 3;
#define TOO_MANY_NON_ZERO_ERR 4

typedef struct until_row_count_list_t until_row_count_list_t;

struct until_row_count_list_t {
    size_t value;
    until_row_count_list_t *next;
};

typedef struct {
    int *values;
    size_t *cols;
    size_t count_cols;
    size_t count_rows;
    size_t count_non_zero;
    until_row_count_list_t row_list;
} sparse_matrix_t;


int create_sparse_matrix(sparse_matrix_t *matrix, const int non_zero_count,
                         const int cols, const int rows);
void free_sparse_matrix(sparse_matrix_t *matrix);
int input_sparse_matrix(sparse_matrix_t *matrix);
void print_sparse_matrix(sparse_matrix_t matrix);
void sparse_matrix_start();
int read_sparse_matrix_from_file(sparse_matrix_t *matrix, const char *filename);
sparse_matrix_t add_sparse_matrix(sparse_matrix_t *first, sparse_matrix_t *second);

#endif

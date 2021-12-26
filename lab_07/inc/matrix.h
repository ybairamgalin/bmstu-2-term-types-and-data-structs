#ifndef __MATRIX_H__
#define __MATRIX_H__

#define INPUT_ERR 2
#define MEM_ERR 3

#define MAX(a, b) (a >= b) ? a : b

typedef struct
{
    int **values;
    int rows;
    int cols;
} matrix_t;

int create_matrix(matrix_t *matrix, const int rows, const int cols);
int input_matrix(matrix_t *matrix);
void print_matrix(const matrix_t matrix);
void free_matrix(matrix_t *matrix);

int make_square_matrix(matrix_t *matrix);
void delete_matrix_row(matrix_t *matrix, const int row);
int expand_matrix(matrix_t *matrix, const int new_sz);
matrix_t multiply_matrix(const matrix_t first, const matrix_t second);
int input_powers(int *p, int *q);
matrix_t pow_matrix(const matrix_t matrix, const int pow);
int mem_allocated(const matrix_t matrix);
void matrix_cpy(matrix_t *dest, const matrix_t src);

#endif

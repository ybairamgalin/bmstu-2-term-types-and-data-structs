#include <stdio.h>
#include <stdlib.h>
#include "../inc/sparse_matrix.h"

int main(void)
{
    sparse_matrix_t sparse_matrix;

    create_sparse_matrix(&sparse_matrix, 8, 3, 5);

    free_sparse_matrix(&sparse_matrix);

    return EXIT_SUCCESS;
}

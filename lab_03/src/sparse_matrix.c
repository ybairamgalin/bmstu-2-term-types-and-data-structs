#include <stdlib.h>
#include <stdio.h>
#include "../inc/sparse_matrix.h"

int create_row_list_elem(until_row_count_list_t *head, const size_t value)
{
    until_row_count_list_t *new = malloc(sizeof(until_row_count_list_t));

    if (new == NULL)
        return MEM_ERR;

    new->next = NULL;
    new->value = value;
    head->next = new;

    return EXIT_SUCCESS;
}

void free_row_list_elem(until_row_count_list_t *head)
{
    if (head->next != NULL)
        free_row_list_elem(head->next);

    free(head);
}

void free_sparse_matrix(sparse_matrix_t *matrix)
{
    free(matrix->values);
    free(matrix->cols);
    free_row_list_elem(matrix->row_list.next);
}

int create_sparse_matrix(sparse_matrix_t *matrix, const int non_zero_count,
        const int cols, const int rows)
{
    matrix->values = malloc(sizeof(int) * non_zero_count);

    if (matrix->values == NULL)
        return MEM_ERR;

    matrix->cols = malloc(sizeof(size_t) * cols);

    if (matrix->cols == NULL)
        return MEM_ERR;

    matrix->row_list.value = 0;

    if (create_row_list_elem(&(matrix->row_list), 0 ) != EXIT_SUCCESS)
        return MEM_ERR;

    until_row_count_list_t *new_head = &(matrix->row_list);

    for (int i = 0; i < rows; i++)
    {
        if (create_row_list_elem(new_head, 0) != EXIT_SUCCESS)
            return MEM_ERR;

        new_head = new_head->next;
    }
    matrix->count_cols = cols;
    matrix->count_rows = rows;
    matrix->count_non_zero = non_zero_count;

    return EXIT_SUCCESS;
}

int add_matrix_row(sparse_matrix_t *matrix, int *non_zero)
{
    int num;
    int non_zero_in_row = 0;

    for (int j = 0; j < matrix->count_cols; j++)
    {
        if (scanf("%d", &num) != 1)
            return INPUT_ERR;

        if (num != 0)
        {
            if (*non_zero >= matrix->count_non_zero)
                return TOO_MANY_NON_ZERO_ERR;

            matrix->values[*non_zero + non_zero_in_row] = num;
            matrix->cols[*non_zero + non_zero_in_row] = j;
        }
    }

    *non_zero += non_zero_in_row;
    printf("Row added\n");

    return EXIT_SUCCESS;
}

int input_sparse_matrix(sparse_matrix_t *matrix)
{
    printf("Matrix input\n");
    int cur_non_zero = 0;

    for (int i = 0; i < matrix->count_rows; i++)
    {
        printf("Enter % row ((%d integers divided with space)):\n", i + 1, matrix->count_cols);

        add_matrix_row(matrix, &cur_non_zero);
    }

    return EXIT_SUCCESS;
}
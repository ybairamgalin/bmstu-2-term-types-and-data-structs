#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

#ifndef INF
#include <limits.h>
#define INF INT_MAX
#endif

int create_matrix(matrix_t *matrix, const int rows, const int cols)
{
    matrix->rows = rows;
    matrix->cols = cols;

    matrix->values = malloc(matrix->rows * sizeof(int*));

    if (matrix->values == NULL)
        return EXIT_FAILURE;

    for (int i = 0; i < matrix->rows; i++)
    {
        matrix->values[i] = malloc(matrix->cols * sizeof(int));

        if (matrix->values[i] == NULL)
        {
            for (int j = i; j >= 0; j++)
                free(matrix->values[i]);

            free(matrix->values);

            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

void free_matrix(matrix_t *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
        free(matrix->values[i]);

    free(matrix->values);
}

int input_row(matrix_t *matrix, const int row)
{
    for (int i = 0; i < matrix->cols; i++)
        if (scanf("%d", &matrix->values[row][i]) != 1)
            return INPUT_ERR;

    return EXIT_SUCCESS;
}

int input_matrix(matrix_t *matrix)
{
    int cols, rows;

    if (scanf("%d", &rows) != 1)
        return INPUT_ERR;

    if (rows <= 0)
        return INPUT_ERR;

    if (scanf("%d", &cols) != 1)
        return INPUT_ERR;

    if (cols <= 0)
        return INPUT_ERR;

    if (create_matrix(matrix, rows, cols) != EXIT_SUCCESS)
        return MEM_ERR;

    for (int i = 0; i < matrix->rows; i++)
        if (input_row(matrix, i) != EXIT_SUCCESS)
        {
            free_matrix(matrix);
            return INPUT_ERR;
        }

    return EXIT_SUCCESS;
}

int input_powers(int *p, int *q)
{
    if (scanf("%d", p) != 1)
        return INPUT_ERR;

    if (*p < 0)
        return INPUT_ERR;

    if (scanf("%d", q) != 1)
        return INPUT_ERR;

    if (*q < 0)
        return INPUT_ERR;

    return EXIT_SUCCESS;
}

int row_max_elem(const matrix_t matrix)
{
    int max = matrix.values[0][0];
    int max_index = 0;

    for (int i = 0; i < matrix.rows; i++)
        for (int j = 0; j < matrix.cols; j++)
            if (matrix.values[i][j] > max)
            {
                max = matrix.values[i][j];
                max_index = i;
            }

    return max_index;
}

int col_max_elem(const matrix_t matrix)
{
    int max = matrix.values[0][0];
    int max_index = 0;

    for (int i = 0; i < matrix.rows; i++)
        for (int j = 0; j < matrix.cols; j++)
            if (matrix.values[i][j] > max)
            {
                max = matrix.values[i][j];
                max_index = j;
            }

    return max_index;
}

void delete_matrix_row(matrix_t *matrix, const int row)
{
    free(matrix->values[row]);

    for (int i = row; i < matrix->rows - 1; i++)
        matrix->values[i] = matrix->values[i + 1];

    (matrix->rows)--;
}

int delete_matrix_col(matrix_t *matrix, const int col)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = col; j < matrix->cols - 1; j++)
            matrix->values[i][j] = matrix->values[i][j + 1];

        matrix->values[i] = realloc(matrix->values[i], sizeof(int) *
                                                       matrix->cols - 1);

        if (matrix->values[i] == NULL)
            return MEM_ERR;
    }

    (matrix->cols)--;

    return EXIT_SUCCESS;
}

int make_square_matrix(matrix_t *matrix)
{
    while (matrix->rows != matrix->cols)
    {
        if (matrix->rows > matrix->cols)
        {
            int to_del_row = row_max_elem(*matrix);
            delete_matrix_row(matrix, to_del_row);
        }
        else if (matrix->rows < matrix->cols)
        {
            int to_del_col = col_max_elem(*matrix);

            if (delete_matrix_col(matrix, to_del_col) != EXIT_SUCCESS)
                return MEM_ERR;
        }
    }

    return EXIT_SUCCESS;
}

int avg_matrix_col(matrix_t *matrix, const int col)
{
    int sum = 0;

    for (int i = 0; i < matrix->rows; i++)
        sum += matrix->values[i][col];

    return (int)(floor((double)sum / (double)matrix->rows));
}

int add_rows_avg(matrix_t *matrix, const int count_new)
{
    int total_rows = matrix->rows + count_new;

    matrix->values = realloc(matrix->values, sizeof(int *) * total_rows);

    if (matrix->values == NULL)
        return MEM_ERR;

    for (int i = matrix->rows; i < total_rows; i++)
    {
        matrix->values[i] = malloc(sizeof(int) * matrix->cols);

        if (matrix->values[i] == NULL)
            return MEM_ERR;

        for (int j = 0; j < matrix->cols; j++)
            matrix->values[i][j] = avg_matrix_col(matrix, j);

        (matrix->rows)++;
    }

    return EXIT_SUCCESS;
}

int max_in_row(const matrix_t matrix, const int row)
{
    int max = matrix.values[row][0];

    for (int i = 0; i < matrix.cols; i++)
        if (matrix.values[row][i] > max)
            max = matrix.values[row][i];

    return max;
}

int add_cols_max(matrix_t *matrix, const int count_new)
{
    int total_cols = matrix->cols + count_new;

    for (int i = 0; i < matrix->rows; i++)
    {
        matrix->values[i] = realloc(matrix->values[i],
                                    sizeof(int) * total_cols);

        if (matrix->values[i] == NULL)
            return MEM_ERR;

        for (int j = matrix->cols; j < total_cols; j++)
            matrix->values[i][j] = max_in_row(*matrix, i);
    }

    matrix->cols = total_cols;

    return EXIT_SUCCESS;
}

int expand_matrix(matrix_t *matrix, const int new_sz)
{
    int error;

    if ((error = add_rows_avg(matrix, new_sz - matrix->rows)) != EXIT_SUCCESS)
        return error;

    if ((error = add_cols_max(matrix, new_sz - matrix->cols)) != EXIT_SUCCESS)
        return error;

    return EXIT_SUCCESS;
}

matrix_t identity_matrix(const int dims)
{
    matrix_t result;

    create_matrix(&result, dims, dims);

    if (result.values == NULL)
    {
        return result;
    }

    for (int i = 0; i < result.rows; i++)
        for (int j = 0; j < result.cols; j++)
            if (i == j)
                result.values[i][j] = 1;
            else
                result.values[i][j] = 0;

    return result;
}

void matrix_cpy(matrix_t *dest, const matrix_t src)
{
    dest->rows = src.rows;
    dest->cols = src.cols;

    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
            dest->values[i][j] = src.values[i][j];
}

// pow == 1
matrix_t pow_matrix(const matrix_t matrix, const int pow)
{
    if (pow == 0)
        return identity_matrix(matrix.cols);

    matrix_t result;

    if (pow == 1)
    {
        if (create_matrix(&result, matrix.rows, matrix.cols) != EXIT_SUCCESS)
        {
            result.values = NULL;
            return result;
        }

        matrix_cpy(&result, matrix);
        return result;
    }

    matrix_t prev;

    if (create_matrix(&prev, matrix.rows, matrix.cols) != EXIT_SUCCESS)
    {
        result.values = NULL;
        return result;
    }

    matrix_cpy(&prev, matrix);

    for (int i = 1; i < pow; i++)
    {
        result = multiply_matrix(prev, matrix);
        free_matrix(&prev);
        prev = result;
    }

    return result;
}

matrix_t multiply_matrix(const matrix_t first, const matrix_t second)
{
    matrix_t result;

    if (create_matrix(&result, first.rows, second.cols) != EXIT_SUCCESS)
    {
        result.values = NULL;
        return result;
    }

    for (int i = 0; i < result.rows; i++)
        for (int j = 0; j < result.cols; j++)
        {
            result.values[i][j] = 0;

            for (int k = 0; k < first.cols; k++)
                result.values[i][j] += first.values[i][k] * second.values[k][j];
        }

    return result;
}

void print_matrix(const matrix_t matrix)
{
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            if (matrix.values[i][j] == INF)
            {
                printf("%7s ", "∞");
                continue;
            }

            printf("%5d ", matrix.values[i][j]);
        }

        printf("\n");
    }
}

int mem_allocated(const matrix_t matrix)
{
    if (matrix.values == NULL)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

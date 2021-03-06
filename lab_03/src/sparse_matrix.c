#include <stdlib.h>
#include <stdio.h>
#include "sparse_matrix.h"

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

    matrix->cols = malloc(sizeof(size_t) * non_zero_count);

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

int add_matrix_row(sparse_matrix_t *matrix, int *non_zero, FILE *file)
{
    int num;
    int non_zero_in_row = 0;

    for (int j = 0; j < matrix->count_cols; j++)
    {
        if (fscanf(file, "%d", &num) != 1)
            return INPUT_ERR;

        if (num != 0)
        {
            if (*non_zero >= matrix->count_non_zero)
                return TOO_MANY_NON_ZERO_ERR;

            matrix->values[*non_zero + non_zero_in_row] = num;
            matrix->cols[*non_zero + non_zero_in_row] = j;
            non_zero_in_row++;
        }
    }

    *non_zero += non_zero_in_row;

    return EXIT_SUCCESS;
}

int read_sparse_matrix_from_file(sparse_matrix_t *matrix, const char *filename)
{
    FILE* file = fopen(filename, "r");

    size_t rows_max, cols_max, non_zero_max;

    if (fscanf(file, "%lld", &rows_max) != 1)
        return INPUT_ERR;

    if (fscanf(file, "%lld", &cols_max) != 1)
        return INPUT_ERR;

    if (fscanf(file, "%lld", &non_zero_max) != 1)
        return INPUT_ERR;

    create_sparse_matrix(matrix, non_zero_max, cols_max, rows_max);
    int non_zero_cur = 0;
    until_row_count_list_t *head = &(matrix->row_list);

    for (int i = 0; i < matrix->count_rows; i++)
    {
        head = head->next;
        add_matrix_row(matrix, &non_zero_cur, file);
        head->value = non_zero_cur;
    }

    fclose(file);

    return EXIT_SUCCESS;
}

typedef struct {
    int row;
    int col;
    int value;
} coords_t;

int cmp_coord_values(const void *first, const void *second)
{
    coords_t *fir = (coords_t*)first;
    coords_t *sec = (coords_t*)second;

    if (fir->row < sec->row)
        return -1;

    if (fir->row > sec->row)
        return 1;

    if (fir->col < sec->col)
        return -1;

    if (fir->col > sec->col)
        return 1;

    return 0;
}

int input_sparse_matrix(sparse_matrix_t *matrix, const int rows, const int cols)
{
    int rows_max, cols_max, non_zero_max;

    printf("Enter number of rows:\n");

    if (scanf("%d", &rows_max) != 1)
        return INPUT_ERR;

    if (rows != ANY_SZ)
        if (rows_max != rows)
        {
            printf("Cannot add such 2 matrices\n");
            return INPUT_ERR;
        }

    if (rows_max <= 0)
        return INPUT_ERR;

    printf("Enter number of cols:\n");

    if (scanf("%d", &cols_max) != 1)
        return INPUT_ERR;

    if (cols != ANY_SZ)
        if (cols_max != cols)
        {
            printf("Cannot add such 2 matrices\n");
            return INPUT_ERR;
        }

    if (cols_max <= 0)
        return INPUT_ERR;

    printf("Enter number of non-zero elements:\n");

    if (scanf("%d", &non_zero_max) != 1)
        return INPUT_ERR;

    if (non_zero_max <= 0)
        return INPUT_ERR;

    create_sparse_matrix(matrix, non_zero_max, cols_max, rows_max);
    int non_zero_cur = 0;
    until_row_count_list_t *head = &(matrix->row_list);

    coords_t values[1000];

    for (int i = 0; i < matrix->count_non_zero; i++)
    {
        coords_t coord_value;
        printf("Input non-zero element %d\n", i + 1);
        printf("Input row: ");

        if (scanf("%d", &coord_value.row) != 1)
            return INPUT_ERR;

        if (coord_value.row < 0 || coord_value.row >= matrix->count_rows)
            return INPUT_ERR;

        printf("Input col: ");

        if (scanf("%d", &coord_value.col) != 1)
            return INPUT_ERR;

        if (coord_value.col < 0 || coord_value.col >= matrix->count_cols)
            return INPUT_ERR;

        printf("Input value: ");

        if (scanf("%d", &coord_value.value) != 1)
            return INPUT_ERR;

        values[non_zero_cur++] = coord_value;
    }

    qsort(values, non_zero_cur, sizeof(coords_t), cmp_coord_values);

    for (int i = 0; i < matrix->count_non_zero; i++)
    {
        if (values[i].value != 0)
        {
            matrix->values[i] = values[i].value;
            matrix->cols[i] = values[i].col;
        }
    }

    int pos = 0;

    for (int i = 0; i < matrix->count_rows; i++)
    {
        head = head->next;

        while (values[pos].row == i)
            pos++;

        head->value = pos;
    }

//    for (int i = 0; i < matrix->count_rows; i++)
//    {
//        head = head->next;
//
//        printf("Enter row %d ((%ld integers divided with space)):\n", i + 1, matrix->count_cols);
//        add_matrix_row(matrix, &non_zero_cur, stdin);
//
//        head->value = non_zero_cur;
//    }

    return EXIT_SUCCESS;
}

void print_sparse_matrix(sparse_matrix_t matrix)
{
    printf("A\t= {");

    for (int i = 0; i < matrix.count_non_zero; i++)
        printf(" %d,", matrix.values[i]);

    printf(" }\n");

    printf("JA\t= {");

    for (int i = 0; i < matrix.count_non_zero; i++)
        printf(" %ld,", matrix.cols[i]);

    printf(" }\n");

    printf("IA\t= {");

    until_row_count_list_t *head = &matrix.row_list;

    for (int i = 0; i < matrix.count_rows + 1; i++)
    {
        printf(" %ld,", head->value);
        head = head->next;
    }

    printf(" }\n");
}

size_t min_size(const size_t first, const size_t second)
{
    if (first <= second)
        return first;

    return second;
}

sparse_matrix_t add_sparse_matrix(sparse_matrix_t *first, sparse_matrix_t *second)
{
    sparse_matrix_t result;

    create_sparse_matrix(&result,min_size(first->count_rows * first->count_cols,
        first->count_non_zero + second->count_non_zero), first->count_cols, first->count_rows);

    until_row_count_list_t *head_first = &(first->row_list);
    until_row_count_list_t *head_second = &(second->row_list);
    until_row_count_list_t *head_result = &(result.row_list);

    size_t cur_non_zero_result = 0;

    while (head_first->next != NULL && head_second->next != NULL)
    {
        int i = head_first->value, j = head_second->value;

        while (i < head_first->next->value || j < head_second->next->value)
        {
            if (i < head_first->next->value && j < head_second->next->value)
            {
                if (first->cols[i] == second->cols[j])
                {
                    if (first->values[i] + second->values[j] == 0)
                    {
                        i++;
                        j++;
                        continue;
                    }

                    result.values[cur_non_zero_result] = first->values[i] + second->values[j];
                    result.cols[cur_non_zero_result] = first->cols[i];
                    i++;
                    j++;
                    cur_non_zero_result++;
                    continue;
                }

                if (first->cols[i] < second->cols[j])
                {
                    result.values[cur_non_zero_result] = first->values[i];
                    result.cols[cur_non_zero_result] = first->cols[i];
                    i++;
                    cur_non_zero_result++;
                    continue;
                }

                if (second->cols[j] < first->cols[i])
                {
                    result.values[cur_non_zero_result] = second->values[j];
                    result.cols[cur_non_zero_result] = second->cols[j];
                    j++;
                    cur_non_zero_result++;
                    continue;
                }
            }
            else
            {
                if (i < head_first->next->value)
                {
                    result.values[cur_non_zero_result] = first->values[i];
                    result.cols[cur_non_zero_result] = first->cols[i];
                    i++;
                    cur_non_zero_result++;
                    continue;
                }
                if (j < head_second->next->value)
                {
                    result.values[cur_non_zero_result] = second->values[j];
                    result.cols[cur_non_zero_result] = second->cols[j];
                    j++;
                    cur_non_zero_result++;
                    continue;
                }
            }
        }

        head_first = head_first->next;
        head_second = head_second->next;

        head_result->next->value = cur_non_zero_result;
        head_result = head_result->next;
    }

    result.values = realloc(result.values, sizeof(int) * cur_non_zero_result);
    result.cols = realloc(result.cols, sizeof(size_t) * cur_non_zero_result);

    result.count_non_zero = cur_non_zero_result;

    return result;
}

void sparse_matrix_start()
{
    printf("Matrix input mode\nOnly use positive integers during input\n\n");
    sparse_matrix_t first, second;

    printf("For matrix 1\n");

    if (input_sparse_matrix(&first, ANY_SZ, ANY_SZ) != EXIT_SUCCESS)
    {
        printf("Matrix input error\n");
        return;
    }

    printf("For matrix 2\n");

    if (input_sparse_matrix(&second, first.count_rows, first.count_cols) != EXIT_SUCCESS)
    {
        printf("Matrix input error\n");
        return;
    }

    if (first.count_cols != second.count_cols)
    {
        printf("Cols count is different, cannot add\n");
        return;
    }

    if (first.count_rows != second.count_rows)
    {
        printf("Row count is different, cannot add\n");
        return;
    }

    sparse_matrix_t result = add_sparse_matrix(&first, &second);

    printf("Result:\n");
    print_sparse_matrix(result);

    free_sparse_matrix(&first);
    free_sparse_matrix(&second);
    free_sparse_matrix(&result);
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>
#include "../inc/matrix.h"
#include "../inc/sparse_matrix.h"

int64_t measure_sparse_matrix_add_time(const char *first_filename,
                                       const char *second_filename, const int times,
                                       size_t *mem_taken)
{
    sparse_matrix_t first, second;
    read_sparse_matrix_from_file(&first, first_filename);
    read_sparse_matrix_from_file(&second, second_filename);

    int64_t elapsed_time = 0;
    struct timeval start, end;

    for (int i = 0; i < times; i++)
    {
        gettimeofday(&start, NULL);
        sparse_matrix_t result = add_sparse_matrix(&first, &second);
        gettimeofday(&end, NULL);
        elapsed_time += (end.tv_sec - start.tv_sec) *
                        1000000LL + (end.tv_usec - start.tv_usec);

        *mem_taken = result.count_non_zero * sizeof(int) * 2 +
                result.count_rows * sizeof(int) + sizeof(int*) + sizeof(int) * 2;

        free_sparse_matrix(&result);
    }

    free_sparse_matrix(&first);
    free_sparse_matrix(&second);


    elapsed_time += (end.tv_sec - start.tv_sec) *
                    1000000LL + (end.tv_usec - start.tv_usec);

    return elapsed_time;
}

int64_t measure_matrix_add_time(const char *first_filename,
                                const char *second_filename, const int times)
{
    matrix_t first, second;
    read_matrix_from_file(&first, first_filename);
    read_matrix_from_file(&second, second_filename);

    int64_t elapsed_time = 0;
    struct timeval start, end;

    for (int i = 0; i < times; i++)
    {
        gettimeofday(&start, NULL);
        matrix_t result = add_matrix(&first, &second);
        gettimeofday(&end, NULL);

        size_t memory_taken = sizeof(first.values);
        printf("%ld\n", memory_taken);

        elapsed_time += (end.tv_sec - start.tv_sec) *
                        1000000LL + (end.tv_usec - start.tv_usec);

        free_matrix(&result);
    }

    free_matrix(&first);
    free_matrix(&second);


    elapsed_time += (end.tv_sec - start.tv_sec) *
                    1000000LL + (end.tv_usec - start.tv_usec);

    return elapsed_time;
}

void eval_time()
{
    size_t mem_250_2, mem_250_5, mem_250_10, mem_250_15, mem_250_20, mem_250_30,
    mem_250_40, mem_250_50, mem_250_60;
    size_t mem_500_2, mem_500_5, mem_500_10, mem_500_15, mem_500_20, mem_500_30,
            mem_500_40, mem_500_50, mem_500_60;

    int64_t elapsed_sparse_250_2 = measure_sparse_matrix_add_time(
            "../lab_03/data/250x250_2_1.txt", "../lab_03/data/250x250_2_2.txt",
            1000);
    int64_t elapsed_sparse_250_5 = measure_sparse_matrix_add_time(
            "../lab_03/data/250x250_5_1.txt", "../lab_03/data/250x250_5_2.txt",
            1000);
    int64_t elapsed_sparse_250_10 = measure_sparse_matrix_add_time(
            "../lab_03/data/250x250_10_1.txt", "../lab_03/data/250x250_10_2.txt",
            1000);
    int64_t elapsed_sparse_250_15 = measure_sparse_matrix_add_time(
            "../lab_03/data/250x250_15_1.txt", "../lab_03/data/250x250_15_2.txt",
            1000);
    int64_t elapsed_sparse_250_20 = measure_sparse_matrix_add_time(
            "../lab_03/data/250x250_20_1.txt", "../lab_03/data/250x250_20_2.txt",
            1000);
    int64_t elapsed_sparse_250_30 = measure_sparse_matrix_add_time(
            "../lab_03/data/250x250_30_1.txt", "../lab_03/data/250x250_30_2.txt",
            1000);
    int64_t elapsed_sparse_250_40 = measure_sparse_matrix_add_time(
            "../lab_03/data/250x250_40_1.txt", "../lab_03/data/250x250_40_2.txt",
            1000);
    int64_t elapsed_sparse_250_50 = measure_sparse_matrix_add_time(
            "../lab_03/data/250x250_50_1.txt", "../lab_03/data/250x250_50_2.txt",
            1000);
    int64_t elapsed_sparse_250_60 = measure_sparse_matrix_add_time(
            "../lab_03/data/250x250_60_1.txt", "../lab_03/data/250x250_60_2.txt",
            1000);

    int64_t elapsed_sparse_500_2 = measure_sparse_matrix_add_time(
            "../lab_03/data/500x500_2_1.txt", "../lab_03/data/500x500_2_2.txt",
            1000);
    int64_t elapsed_sparse_500_5 = measure_sparse_matrix_add_time(
            "../lab_03/data/500x500_5_1.txt", "../lab_03/data/500x500_5_2.txt",
            1000);
    int64_t elapsed_sparse_500_10 = measure_sparse_matrix_add_time(
            "../lab_03/data/500x500_10_1.txt", "../lab_03/data/500x500_10_2.txt",
            1000);
    int64_t elapsed_sparse_500_15 = measure_sparse_matrix_add_time(
            "../lab_03/data/500x500_15_1.txt", "../lab_03/data/500x500_15_2.txt",
            1000);
    int64_t elapsed_sparse_500_20 = measure_sparse_matrix_add_time(
            "../lab_03/data/500x500_20_1.txt", "../lab_03/data/500x500_20_2.txt",
            1000);
    int64_t elapsed_sparse_500_30 = measure_sparse_matrix_add_time(
            "../lab_03/data/500x500_30_1.txt", "../lab_03/data/500x500_30_2.txt",
            1000);
    int64_t elapsed_sparse_500_40 = measure_sparse_matrix_add_time(
            "../lab_03/data/500x500_40_1.txt", "../lab_03/data/500x500_40_2.txt",
            1000);
    int64_t elapsed_sparse_500_50 = measure_sparse_matrix_add_time(
            "../lab_03/data/500x500_50_1.txt", "../lab_03/data/500x500_50_2.txt",
            1000);
    int64_t elapsed_sparse_500_60 = measure_sparse_matrix_add_time(
            "../lab_03/data/500x500_60_1.txt", "../lab_03/data/500x500_60_2.txt",
            1000);

    printf("FOR SPARSE MATRIX\n\n");

    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "2", elapsed_sparse_250_2);
    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "5", elapsed_sparse_250_5);
    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "10", elapsed_sparse_250_10);
    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "15", elapsed_sparse_250_15);
    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "20", elapsed_sparse_250_20);
    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "30", elapsed_sparse_250_30);
    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "40", elapsed_sparse_250_40);
    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "50", elapsed_sparse_250_50);
    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "60", elapsed_sparse_250_60);
    printf("\n");

    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "2", elapsed_sparse_500_2);
    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "5", elapsed_sparse_500_5);
    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "10", elapsed_sparse_500_10);
    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "15", elapsed_sparse_500_15);
    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "20", elapsed_sparse_500_20);
    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "30", elapsed_sparse_500_30);
    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "40", elapsed_sparse_500_40);
    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "50", elapsed_sparse_500_50);
    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "60", elapsed_sparse_500_60);
    printf("\n");

    elapsed_sparse_250_2 = measure_matrix_add_time(
            "../lab_03/data/250x250_2_1.txt", "../lab_03/data/250x250_2_2.txt",
            1000);
    elapsed_sparse_250_5 = measure_matrix_add_time(
            "../lab_03/data/250x250_5_1.txt", "../lab_03/data/250x250_5_2.txt",
            1000);
    elapsed_sparse_250_10 = measure_matrix_add_time(
            "../lab_03/data/250x250_10_1.txt", "../lab_03/data/250x250_10_2.txt",
            1000);
    elapsed_sparse_250_15 = measure_matrix_add_time(
            "../lab_03/data/250x250_15_1.txt", "../lab_03/data/250x250_15_2.txt",
            1000);
    elapsed_sparse_250_20 = measure_matrix_add_time(
            "../lab_03/data/250x250_20_1.txt", "../lab_03/data/250x250_20_2.txt",
            1000);
    elapsed_sparse_250_30 = measure_matrix_add_time(
            "../lab_03/data/250x250_30_1.txt", "../lab_03/data/250x250_30_2.txt",
            1000);
    elapsed_sparse_250_40 = measure_matrix_add_time(
            "../lab_03/data/250x250_40_1.txt", "../lab_03/data/250x250_40_2.txt",
            1000);
    elapsed_sparse_250_50 = measure_matrix_add_time(
            "../lab_03/data/250x250_50_1.txt", "../lab_03/data/250x250_50_2.txt",
            1000);
    elapsed_sparse_250_60 = measure_matrix_add_time(
            "../lab_03/data/250x250_60_1.txt", "../lab_03/data/250x250_60_2.txt",
            1000);

    elapsed_sparse_500_2 = measure_matrix_add_time(
            "../lab_03/data/500x500_2_1.txt", "../lab_03/data/500x500_2_2.txt",
            1000);
    elapsed_sparse_500_5 = measure_matrix_add_time(
            "../lab_03/data/500x500_5_1.txt", "../lab_03/data/500x500_5_2.txt",
            1000);
    elapsed_sparse_500_10 = measure_matrix_add_time(
            "../lab_03/data/500x500_10_1.txt", "../lab_03/data/500x500_10_2.txt",
            1000);
    elapsed_sparse_500_15 = measure_matrix_add_time(
            "../lab_03/data/500x500_15_1.txt", "../lab_03/data/500x500_15_2.txt",
            1000);
    elapsed_sparse_500_20 = measure_matrix_add_time(
            "../lab_03/data/500x500_20_1.txt", "../lab_03/data/500x500_20_2.txt",
            1000);
    elapsed_sparse_500_30 = measure_matrix_add_time(
            "../lab_03/data/500x500_30_1.txt", "../lab_03/data/500x500_30_2.txt",
            1000);
    elapsed_sparse_500_40 = measure_matrix_add_time(
            "../lab_03/data/500x500_40_1.txt", "../lab_03/data/500x500_40_2.txt",
            1000);
    elapsed_sparse_500_50 = measure_matrix_add_time(
            "../lab_03/data/500x500_50_1.txt", "../lab_03/data/500x500_50_2.txt",
            1000);
    elapsed_sparse_500_60 = measure_matrix_add_time(
            "../lab_03/data/500x500_60_1.txt", "../lab_03/data/500x500_60_2.txt",
            1000);

    printf("FOR REGULAR MATRIX\n\n");

    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "2", elapsed_sparse_250_2);
    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "5", elapsed_sparse_250_5);
    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "10", elapsed_sparse_250_10);
    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "15", elapsed_sparse_250_15);
    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "20", elapsed_sparse_250_20);
    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "30", elapsed_sparse_250_30);
    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "40", elapsed_sparse_250_40);
    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "50", elapsed_sparse_250_50);
    printf("MATRIX 250x250 FILLED %3s%%: %20lld\n", "60", elapsed_sparse_250_60);
    printf("\n");

    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "2", elapsed_sparse_500_2);
    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "5", elapsed_sparse_500_5);
    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "10", elapsed_sparse_500_10);
    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "15", elapsed_sparse_500_15);
    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "20", elapsed_sparse_500_20);
    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "30", elapsed_sparse_500_30);
    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "40", elapsed_sparse_500_40);
    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "50", elapsed_sparse_500_50);
    printf("MATRIX 500x500 FILLED %3s%%: %20lld\n", "60", elapsed_sparse_500_60);
    printf("\n");
}

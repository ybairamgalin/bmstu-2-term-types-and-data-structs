#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <inttypes.h>
#include <time.h>
#include "hash_table.h"
#include "data.h"
#include "bin_tree.h"

#define FIND_TIMES 10q

int read_string(FILE *file, char *buf)
{
    if (fgets(buf, 40, file) == NULL)
        return EXIT_FAILURE;

    if (buf[strlen(buf) - 1] != '\n')
    {
        fprintf(stderr, "Word is too long\n");
        return EXIT_FAILURE;
    }

    buf[strlen(buf) - 1] = '\0';

    return EXIT_SUCCESS;
}

void measure_time_find(const char *restrict filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Data file does not exist");
        return;
    }

    printf("Opened successfully\n");

    hash_table_t *table = hash_table_create(NULL);
    bin_tree_t *tree_balanced = NULL;
    bin_tree_t *tree = NULL;
    char buf[100];

    while (read_string(file, buf) == EXIT_SUCCESS)
    {
        hash_table_set(table, data_create(buf));
        tree_balanced = bin_tree_insert(tree_balanced, data_create(buf));
        tree = bin_tree_insert_dn_balance(tree, data_create(buf));
    }

    fclose(file);

    char words_from_file[100000][40];
    int number_words = 0;
    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("ERROR!");
        return;
    }

    while (read_string(file, buf) == EXIT_SUCCESS)
    {
        strcpy(words_from_file[number_words++], buf);
    }


    unsigned long long total_elapsed_tree = 0;
    unsigned long long total_elapsed_tree_balanced = 0;
    unsigned long long total_elapsed_tree_table = 0;
    unsigned long long total_elapsed_tree_file = 0;

    for (int i = 0; i < number_words; i++)
    {
        clock_t begin, end;
        begin = clock();

        for (int j = 0; j < FIND_TIMES; j++)
            bin_tree_find(tree, words_from_file[i]);

        end = clock();
        total_elapsed_tree += end - begin;
        begin = clock();

        for (int j = 0; j < FIND_TIMES; j++)
            bin_tree_find(tree_balanced, words_from_file[i]);

        end = clock();
        total_elapsed_tree_balanced += end - begin;

        begin = clock();

        for (int j = 0; j < FIND_TIMES; j++)
            hash_table_get(table, words_from_file[i]);

        end = clock();
        total_elapsed_tree_table += end - begin;

        for (int j = 0; j < FIND_TIMES; j++)
        {
            fseek(file, 0, SEEK_SET);
            begin = clock();

            while (read_string(file, buf) == EXIT_SUCCESS)
                if (strcmp(buf, words_from_file[i]) == 0)
                    break;

            end = clock();
            total_elapsed_tree_file += end - begin;
        }
    }

    printf("Avg elapsed tree: %lf\n"
           "Avg elapsed balanced tree: %lf\n"
           "Avg elapsed table: %lf\n"
           "Avg elapsed file: %lf\n"
           "\n", (double)total_elapsed_tree / number_words,
           (double)total_elapsed_tree_balanced / number_words,
           (double)total_elapsed_tree_table / number_words,
           (double)total_elapsed_tree_file / number_words);

    fclose(file);
}

int measure_time()
{
    printf("100 elements:\n");
    measure_time_find("../lab_06/data/nums_100");
    printf("\n");

    printf("1000 elements:\n");
    measure_time_find("../lab_06/data/nums_1000");
    printf("\n");

    printf("10000 elements:\n");
    measure_time_find("../lab_06/data/nums_10000");
    printf("\n");

    return EXIT_SUCCESS;
}

int read_num(FILE *file, long *num)
{
    if (!file || !num)
        return EXIT_FAILURE;

    char buf[40];

    if (read_string(file, buf) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    char *end;
    long number = strtol(buf, &end, 10);

    if (buf == end)
    {
        fprintf(stderr, "Non a number\n");
        return EXIT_FAILURE;
    }

    *num = number;

    return  EXIT_SUCCESS;
}

int main(void)
{
    char buf[40];
//    printf("Enter filename that will be used: ");
//
//    if (read_string(stdin, buf) != EXIT_SUCCESS)
//    {
//        fprintf(stderr, "Input error\n");
//        return EXIT_FAILURE;
//    }
//
//    FILE *file = fopen(buf, "r");
    FILE *file = fopen("../lab_06/data/data.txt", "r");

    if (file == NULL)
    {
        fprintf(stderr, "Data file does not exist");
        return EXIT_FAILURE;
    }

    printf("Opened successfully\n");

    hash_table_t *table = hash_table_create(NULL);
    bin_tree_t *tree_balanced = NULL;
    bin_tree_t *tree = NULL;

    while (read_string(file, buf) == EXIT_SUCCESS)
    {
        hash_table_set(table, data_create(buf));
        tree_balanced = bin_tree_insert(tree_balanced, data_create(buf));
        tree = bin_tree_insert_dn_balance(tree, data_create(buf));
    }

    printf("Structures filled\n");

    while (1)
    {
        printf("1 - Show binary search tree\n"
               "2 - Show balanced tree\n"
               "3 - Show hash table\n"
               "4 - Print all nodes in binary search tree\n"
               "5 - Print all nodes in balanced tree\n"
               "6 - Add new field\n"
               "7 - Delete field\n"
               "8 - Find field\n"
               "9 - Measure time\n"
               "0 - Exit\n");

        long num;

        if (read_num(stdin, &num) != EXIT_SUCCESS)
            continue;

        if (num == 1)
        {
            bin_tree_grapfviz(tree);
            printf("Success!\n");
        }
        else if (num == 2)
        {
            bin_tree_grapfviz(tree_balanced);
            printf("Success!\n");
        }
        else if (num == 3)
        {
            hash_table_print(table);
        }
        else if (num == 4)
        {
            bin_tree_show_all_children(tree);
        }
        else if (num == 5)
        {
            bin_tree_show_all_children(tree_balanced);
        }
        else if (num == 6)
        {
            printf("Input new field: ");

            if (read_string(stdin, buf) != EXIT_SUCCESS)
                continue;

            hash_table_set(table, data_create(buf));
            tree_balanced = bin_tree_insert(tree_balanced, data_create(buf));
            tree = bin_tree_insert_dn_balance(tree, data_create(buf));

            printf("Inserted!\n");
        }
        else if (num == 7)
        {
            printf("Input value to delete: ");

            if (read_string(stdin, buf) != EXIT_SUCCESS)
                continue;

            hash_table_remove(table, buf);
            tree = bin_tree_remove(tree, buf);
            tree_balanced = bin_tree_remove(tree_balanced, buf);
        }
        else if (num == 8)
        {
            printf("Input field to find: ");

            if (read_string(stdin, buf) != EXIT_SUCCESS)
                continue;

            data_t *found_balanced = bin_tree_find(tree_balanced, buf);
            data_print(found_balanced);

            data_t *found_tree = bin_tree_find(tree, buf);
            data_print(found_tree);

            data_t *found_table = hash_table_get(table, buf);
            data_print(found_table);
        }
        else if (num == 9)
        {
            measure_time();
        }
        else if (num == 0)
        {
            printf("Closing program...");
            break;
        }
        else
        {
            printf("Unknown command\n");
        }
    }

    return EXIT_SUCCESS;
}

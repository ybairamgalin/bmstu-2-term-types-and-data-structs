#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrix.h"
#include "graph.h"

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

int read_edge(FILE *file, graph_t graph)
{
    int from, to, lng;

    if (fscanf(file, "%d%d%d", &from, &to, &lng) != 3)
        return EXIT_FAILURE;

    if (graph_add_edge(graph, from, to, lng) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int main(void)
{
    printf("Program is made to find...\n"); // TODO
    FILE *file = fopen("../lab_07/data/graph.txt", "r");

    if (file == NULL)
    {
        fprintf(stderr, "Error opening file\n");
        return EXIT_FAILURE;
    }

    int sz;

    if (fscanf(file, "%d", &sz) != 1)
    {
        fprintf(stderr, "Error in file structure\n");
        return EXIT_FAILURE;
    }

    graph_t graph = graph_create(sz);

    while (read_edge(file, graph) == EXIT_SUCCESS);

    while (1)
    {
        printf("1 - Show graph\n"
               "2 - Show adjacency matrix\n"
               "3 - Show table of distances\n"
               "4 - Find city with shortest distance sum\n"
               "5 - Add/change edge\n"
               "6 - Delete edge\n"
               "0 - Exit\n");

        long num;

        if (read_num(stdin, &num) != EXIT_SUCCESS)
            continue;

        if (num == 1)
        {
            grapfviz(graph);
            printf("Shown!\n");
        }
        else if (num == 2)
        {
            graph_print_matrix(graph);
            printf("Shown!\n");
        }
        else if (num == 3)
        {
            matrix_t *paths = graph_shortest_paths_matrix(graph);
            print_matrix(*paths);
        }
        else if (num == 4)
        {
            int index, dist;

            index = graph_city_shortest_dist_sum(graph, &dist);

            printf("Shortest sum of distances is %d, for the city number %d.\n",
                   dist, index + 1);

            graph_reconstruct_paths(graph, index);
        }
        else if (num == 5)
        {

        }
        else if (num == 6)
        {

        }
        else if (num == 0)
        {
            break;
        }
    }

    return EXIT_SUCCESS;
}

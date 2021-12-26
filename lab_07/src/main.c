#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "graph.h"

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

    graph_print_matrix(graph);
//    grapfviz(graph);

    matrix_t *paths = graph_shortest_paths_matrix(graph);
    printf("\n");

    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j < sz; j++)
            printf("%5d ", paths->values[i][j]);

        printf("\n");
    }

    return EXIT_SUCCESS;
}

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "matrix.h"
#include "graph.h"

#ifndef INF
#define INF INT_MAX
#endif

struct graph
{
    matrix_t *adjacency_matrix;
    int sz;
};

graph_t graph_create(const int sz)
{
    graph_t graph = malloc(sizeof(struct graph));

    if (graph == NULL)
        return NULL;

    graph->sz = sz;
    graph->adjacency_matrix = malloc(sizeof(matrix_t));

    if (graph->adjacency_matrix == NULL)
        return NULL;

    if (create_matrix(graph->adjacency_matrix, graph->sz, graph->sz) != EXIT_SUCCESS)
    {
        free(graph);
        return NULL;
    }

    for (int i = 0; i < graph->sz; i++)
        for (int j = 0; j < graph->sz; j++)
            graph->adjacency_matrix->values[i][j] = (i == j) ? 0 : INF;

    return graph;
}

int graph_add_edge(graph_t graph, const int from, const int to,
const int lng)
{
    if (from <= 0 || from > graph->sz)
        return EXIT_FAILURE;

    if (to <= 0 || to > graph->sz)
        return EXIT_FAILURE;

    graph->adjacency_matrix->values[from - 1][to - 1] = lng;
    graph->adjacency_matrix->values[to - 1][from - 1] = lng;

    return EXIT_SUCCESS;
}

matrix_t *graph_shortest_paths_matrix(graph_t graph)
{
    matrix_t *paths = malloc(sizeof(matrix_t));

    if (create_matrix(paths, graph->sz, graph->sz) != EXIT_SUCCESS)
        return NULL;

    matrix_cpy(paths, *(graph->adjacency_matrix));

    for (int k = 0; k < graph->sz; k++)
        for (int i = 0; i < graph->sz; i++)
            for (int j = 0; j < graph->sz; j++)
            {
                if (paths->values[i][k] == INF || paths->values[k][j] == INF)
                    continue;

                if (paths->values[i][j] > paths->values[i][k] + paths->values[k][j])
                    paths->values[i][j] = paths->values[i][k] + paths->values[k][j];
            }

    return paths;
}

matrix_t *graph_shortest_paths_paths(graph_t graph)
{
    matrix_t *paths = malloc(sizeof(matrix_t));
    matrix_t *next = malloc(sizeof(matrix_t));

    if (create_matrix(paths, graph->sz, graph->sz) != EXIT_SUCCESS)
        return NULL;

    if (create_matrix(next, graph->sz, graph->sz) != EXIT_SUCCESS)
        return NULL;

    matrix_cpy(paths, *(graph->adjacency_matrix));

    for (int i = 0; i < graph->sz; i++)
        for (int j = 0; j < graph->sz; j++)
        {
            next->values[i][j] = j;
        }

    for (int k = 0; k < graph->sz; k++)
        for (int i = 0; i < graph->sz; i++)
            for (int j = 0; j < graph->sz; j++)
            {
                if (paths->values[i][k] == INF || paths->values[k][j] == INF)
                    continue;

                if (paths->values[i][j] > paths->values[i][k] + paths->values[k][j])
                {
                    paths->values[i][j] = paths->values[i][k] + paths->values[k][j];
                    next->values[i][j] = next->values[i][k];
                }
            }

    return next;
}

void graph_print_matrix(graph_t graph)
{
    print_matrix(*(graph->adjacency_matrix));
//    for (int i = 0; i < graph->sz; i++)
//    {
//        for (int j = 0; j < graph->sz; j++)
//            if (graph->adjacency_matrix->values[i][j] != INF)
//                printf("%5d ", graph->adjacency_matrix->values[i][j]);
//            else
//                printf("%7s ", "∞");
//
//        printf("\n");
//    }
}

int graph_city_shortest_dist_sum(graph_t graph, int *dist)
{
    matrix_t *matrix = graph_shortest_paths_matrix(graph);

    if (matrix == NULL)
    {
        fprintf(stderr, "Error occurred\n");
        return -1;
    }

    int max_sum = INF;
    int index = 0;

    for (int i = 0; i < graph->sz; i++)
    {
        int sum = 0;

        for (int j = 0; j < graph->sz; j++)
        {
            if (matrix->values[i][j] == INF)
            {
                sum = INF;
                break;
            }

             sum += matrix->values[i][j];
        }

        if (sum < max_sum)
        {
            max_sum = sum;
            index = i;
        }
    }

    *dist = max_sum;

    return index;
}

int graph_shortest_path(graph_t graph, const int from, const int to, int *arr, int *sz)
{
    if (arr == NULL || sz == NULL)
    {
        return EXIT_FAILURE;
    }

    if (from > graph->sz || to > graph->sz)
    {
        return EXIT_FAILURE;
    }

    int cur_sz = 0;
    int cur_city = from;
    arr[cur_sz++] = cur_city;

    matrix_t *matrix = graph_shortest_paths_paths(graph);

    if (matrix == NULL)
    {
        fprintf(stderr, "Error occurred\n");
        return -1;
    }

    while (cur_city != to)
    {
        cur_city = matrix->values[cur_city][to];
        arr[cur_sz++] = cur_city;
    }

    *sz = cur_sz;

    return EXIT_SUCCESS;
}

int get_num_cities(graph_t graph)
{
    return graph->sz;
}

void graph_reconstruct_paths(graph_t graph, const int city)
{
    for (int i = 0; i < graph->sz; i++)
    {
        if (i != city)
        {
            int path[100], lng;

            graph_shortest_path(graph, city, i, path, &lng);

            printf("Path from city %d to %d: %d", city + 1, i + 1, city + 1);

            for (int j = 1; j < lng; j++)
                printf(" -> %d", path[j] + 1);

            printf("\n");
        }
    }
}

static void generate_graphviz(FILE *file, graph_t graph)
{
    if (!graph)
        return;

    for (int i = 0; i < graph->sz; i++)
        for (int j = i; j < graph->sz; j++)
        {
            if (graph->adjacency_matrix->values[i][j] != 0 && graph->adjacency_matrix->values[i][j] != INF)
                fprintf(file, "\t%d -> %d [label=%d, dir=none];\n", i + 1, j + 1, graph->adjacency_matrix->values[i][j]);
        }
}

void grapfviz(graph_t graph)
{
    FILE *graphviz_file = fopen("../lab_07/data/tree.gv.txt", "w");

    if (graphviz_file == NULL)
    {
        fprintf(stderr, "Couldn't open graphviz file\n");
        return;
    }

    fprintf(graphviz_file, "digraph BST {\n");
    generate_graphviz(graphviz_file, graph);
    fprintf(graphviz_file, "}\n");
    fclose(graphviz_file);

    system("dot -Tpng ../lab_07/data/tree.gv.txt > ../lab_07/data/out.png");
    system("open ../lab_07/data/out.png");
}

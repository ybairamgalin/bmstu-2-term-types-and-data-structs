#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef struct graph *graph_t;

graph_t graph_create(const int sz);
int graph_add_edge(graph_t graph, const int from, const int to,
                   const int lng);
int get_num_cities(graph_t graph);

matrix_t *graph_shortest_paths_matrix(graph_t graph);
int graph_city_shortest_dist_sum(graph_t graph, int *dist);
int graph_shortest_path(graph_t graph, const int from, const int to, int *arr, int *sz);
void graph_reconstruct_paths(graph_t graph, const int city);

void graph_print_matrix(graph_t graph);
void grapfviz(graph_t graph);

#endif

#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef struct graph *graph_t;

graph_t graph_create(const int sz);
int graph_add_edge(graph_t graph, const int from, const int to,
                   const int lng);

matrix_t *graph_shortest_paths_matrix(graph_t graph);

void graph_print_matrix(graph_t graph);
void grapfviz(graph_t graph);

#endif

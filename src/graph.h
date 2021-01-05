/*
 * =====================================================================================
 *
 *       Filename:  graph.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/10/2020 17:55:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, MPRO
 *
 * =====================================================================================
 */

#ifndef  graph_INC
#define  graph_INC

#include "utils.h"
#include "indicator.h"
#include "queue.h"

struct maillon{
  uint v;
  struct maillon * next;
};

typedef struct maillon * list;

list list_add_sorted(list l, uint v, int* flag);

/* Allocates an array and stores the n firsts elements of l inside.
 * If l is too short, the remaining slots are left untouched.*/
void list_to_array(list l, uint* dest, uint n);

void list_print(list l);

void list_free(list l);

/* this structure represent a graph G=(V,E) with |V| = n and |E| = m;
 * STATIC structure do not try to modify an existing one
 * Remark : the vertex of index 0 represent the point (0, 0)*/
typedef struct graph {
  /* the number of vertices in the graph */
  uint n;

  /* vertices, an array of length n+1;
   * vertices[i+1] - vertices[i] = number of neighbours of i;
   * vertices[n] = m;*/
  uint * vertices;

  /* edges, an array of length m;
   * form edges[vertices[i]] to edges[vertices[i+1]-1]
   * you obtain the neighbours of i;*/
  uint * edges;

  /* weights, an array of length m;
   * weights[i] correspond to the weight of the i-th edge;*/
  int * weights;

} graph_t;

typedef graph_t * graph_p;

/* Structure to represent graphs. The neighbours of each vertex i is
 * stored in a list of length deg(i). So you cannot easily add a vertex
 * but it is allowed to add and remove edges.*/
typedef struct mgraph_t {
  uint n, m;

  /* array of length n */
  uint * deg;

  /* array of length n */
  list * neigh;
} mgraph_t;

typedef mgraph_t * mgraph_p;

mgraph_p mgraph_new(uint n);

/* Return : 0 if the edges was already present in g 
 * otherwise, add the edges and return 1.*/
int mgraph_add_edge(mgraph_p g, uint i, uint j);

mgraph_p mgraph_random(uint n);

mgraph_p mgraph_from_file(char* path);

void mgraph_free(mgraph_p g);

/* returns the degree of i in G*/
#define DEG(G, i)\
  (G->vertices[i+1] - G->vertices[i])

/* after call, N points to the neighbours' array of i of size d */
#define NEIGHS(G, i, N, d)\
  N = G->edges + G->vertices[i]; d = DEG(G, i)

/* iterate over the pointer to neighbour */
#define FOR_ALL_NEIGH(G, i, n)\
  for(n = &(G)->edges[(G)->vertices[i]]; \
      n < &(G)->edges[(G)->vertices[i+1]]; \
      n++)

/* Ensure : the returned pointer is a brand new graph with n vertices
 * and 0 edges.
 * WARNING : 
 *    * ret->edges == NULL;
 *    * ret->weights == NULL;
 *    * malloc.
 * */
graph_p graph_new(uint n);

graph_p graph_from_mgraph(mgraph_p g);

graph_p graph_from_file(char* path);

int graph_to_file(graph_p g, char* path);

graph_p graph_random(uint n);

/* Ensure : performs a deep first search in g from v calling f(v, arg) on
 *    vertex reach. ind indicates the remaining vertices to visit. In order to 
 *    perform a full DFS on g starting on v, ind must be equal to [1..n]\v.
 * Require : v < g->n and validity of g/ind.
 * WARNING : recursive algorithm, may be slow. ind is modified at each call.
 * */
void graph_dfs(graph_p g, ind_p ind, uint v, 
    void(*f)(uint, void*), void* arg);

/* Ensure : release the memory used by g.
 * */
void graph_free(graph_p g);

void graph_print(graph_p g);

#endif   /* ----- #ifndef graph_INC  ----- */

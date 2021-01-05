/*
 * =====================================================================================
 *
 *       Filename:  graph.c
 *
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  20/10/2020 17:54:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, MPRO
 *
 * =====================================================================================
 */

#include "graph.h"

/* LIST */

list list_add_sorted(list l, uint v, int* flag){
  if(l == NULL || l->v > v){
    list r = malloc(sizeof(maillon));
    r->v = v;
    r->next = l;
    *flag = 1;
    return r;
  }
  else {
    if(l->v != v){
      *flag = 0;
      l->next = list_add_sorted(l->next, v);
    }
    return l;
  }
}

uint* list_to_array(list l, uint n){
  uint* ret = malloc(sizeof(uint)*n);
  uint i = 0;
  while(l != NULL && i < n){
    ret[i] = l->v;
    l = l->next;
    i ++;
  }

  return ret;
}

void list_free(list l){
  if(l){
    list_free(l->next);
    free(l);
    l = NULL;
  }
}

/* MGRAPH */

mgraph_p mgraph_new(uint n){
  mgraph_p res = malloc(sizeof(mgraph_t));
  res->n = n;
  res->m = 0;
  res->deg = malloc(sizeof(uint)*n);
  res->neigh = malloc(sizeof(list)*n);
  
  uint i;
  for(i=0; i<n; i++){
    res->deg[i] = 0;
    res->neigh[i] = NULL;
  }

  return res;
}

void mgraph_add_edge(mgraph_p g, uint i, uint j){

}

mgraph_p mgraph_random(uint n){
  uint i, v, cq, cin;
  res = mgraph_new(n);
  queue_p q = queue_new(n);
  for(i=0; i < n-1; i++)
    queue_push(q, i);
  
  queue_p in = queue_new(n);
  queue_push(in, n-1)

  while(card = QUEUE_CARD(q)){
    i = RAND_UINT(card);
    v = queue_pop_id(q, i);

    queue_push(q, v);
  }
}

void mgraph_free(mgraph_p g){
  free(g->deg);
  g->deg = NULL;
  uint i;
  for(i=0; i<g->n; i++){
    free(g->neigh[i]);
    g->neight[i] = NULL;
  }

  free(g);
  g = NULL;
}

/* GRAPH */

graph_p graph_new(uint n){
  graph_p res = malloc(sizeof(graph_t));
  res->n = n;
  res->vertices = malloc(sizeof(uint)*(n+1));
  res->edges = NULL;
  res->weights = NULL;
  return res;
}

/* Deep first search */
void graph_dfs(graph_p g, ind_p ind, uint v, 
    void(*f)(uint, void*),void* arg){
  uint* s;
  if (f) (*f)(v, arg);

  FOR_ALL_NEIGH(g, v, s){
    if(IND_TEST(ind, *s)){
      IND_UNSET(ind, *s);
      graph_dfs(g, ind, *s, f, arg);
    }
  }
}

void graph_free(graph_p g){
  free(g->vertices);
  g->vertices = NULL;
  free(g->edges);
  g->edges = NULL;
  free(g->weights);
  g->weights = NULL;
  free(g);
  g = NULL;
}

void graph_print(graph_p g){
  uint i;
  uint* s;
  for(i=0; i<g->n; i++){
    printf("%d : ", i);
    FOR_ALL_NEIGH(g, i, s){
      printf("%d ", *s);
    }
    printf("\n");
  }
}

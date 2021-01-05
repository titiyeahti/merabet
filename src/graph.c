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
    list r = malloc(sizeof(struct maillon));
    r->v = v;
    r->next = l;
    *flag = 1;
    return r;
  }
  else {
    *flag = 0;
    if(l->v != v){
      l->next = list_add_sorted(l->next, v, flag);
    }
    return l;
  }
}

void list_to_array(list l, uint* dest, uint n){
  uint i = 0;
  while(l != NULL && i < n){
    dest[i] = l->v;
    l = l->next;
    i ++;
  }
}

void list_print(list l){
  if(l){
    printf("%d ", l->v);
    list_print(l->next);
  }
  else 
    printf("\n");
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

int mgraph_add_edge(mgraph_p g, uint i, uint j){
  int flag;

  g->neigh[i] = list_add_sorted(g->neigh[i], j, &flag);
  g->neigh[j] = list_add_sorted(g->neigh[j], i, &flag);
  
  if(flag){
    g->deg[i] ++;
    g->deg[j] ++;
    g->m += 2;
  }

  return flag;
}

mgraph_p mgraph_from_file(char* path){
  FILE* stream;

  stream = fopen(path, "r");
  if(!stream){
    EXIT_ERROR("mgraph_from_file");
  }

  uint n, m, i, j;
  fscanf(stream, "%d %d\n", &n, &m);
  
  mgraph_p res = mgraph_new(n);

  while (m>0){
    fscanf(stream, "%d %d\n", &i, &j);
    mgraph_add_edge(res, i, j);
    m--;
  }
  fclose(stream);
  return res;
}

mgraph_p mgraph_random(uint n){
  uint edges_left = n-1 + 3*( (uint) roundf(sqrtf((float) n)) );
  uint nb_edges = edges_left;
  uint i, v, v2, card, flag;
  mgraph_p res = mgraph_new(n);
  queue_p q = queue_new(n);
  for(i=0; i < n-1; i++)
    queue_push(q, i);
  
  queue_p in = queue_new(n);
  queue_push(in, n-1);

  /* Connected random graph */
  while(card = QUEUE_CARD(q)){
    i = RAND_UINT(card);
    v = queue_pop_id(q, i);

    i = RAND_UINT(QUEUE_CARD(in));
    v2 = in->data[in->bot + i];

    flag = mgraph_add_edge(res, v, v2);
    edges_left -= flag;

    queue_push(in, v);
  }

  while(edges_left){
    v = RAND_UINT(n);
    v2 = RAND_UINT(n-1);

    v2 += v2 < v ? 0 : 1;
  
    flag = mgraph_add_edge(res, v, v2);
    edges_left -= flag;
  }

  queue_free(q);
  queue_free(in);

  return res;
}

void mgraph_free(mgraph_p g){
  free(g->deg);
  g->deg = NULL;
  uint i;
  for(i=0; i<g->n; i++){
    list_free(g->neigh[i]);
    g->neigh[i] = NULL;
  }
  free(g->neigh);
  g->neigh = NULL;

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

graph_p graph_from_mgraph(mgraph_p g){
  uint i;
  graph_p res = graph_new(g->n);

  res->vertices[0] = 0;
  for(i=1; i<res->n+1; i++)
    res->vertices[i] = res->vertices[i-1] + g->deg[i-1];

  res->weights = malloc(sizeof(uint)*g->m);
  for(i=0; i<g->m; i++){
    res->weights[i] = 0;
  }
  
  res->edges = malloc(sizeof(uint)*g->m);
  for(i=0; i<res->n; i++){
    list_to_array(g->neigh[i], &(res->edges[res->vertices[i]]),
        res->vertices[i+1] - res->vertices[i]);
  }

  return res;
}

graph_p graph_from_file(char* path){
  mgraph_p g = mgraph_from_file(path);
  graph_p res = graph_from_mgraph(g);
  mgraph_free(g);
  return res;
}

int graph_to_file(graph_p g, char* path){
  FILE* stream;
  stream = fopen(path, "w");
  if(!stream){
    EXIT_ERROR("graph_to_file");
  }
  uint m = g->vertices[g->n] / 2;
  
  fprintf(stream, "%d %d\n", g->n, m);

  uint i;
  uint *v;
  for(i=0; i<g->n && m>0; i++){
    FOR_ALL_NEIGH(g, i, v){
      if (*v>i){
        fprintf(stream, "%d %d\n", i, *v);
        m --;
      }
    }
  }

  fclose(stream);
  return 1;
}

graph_p graph_random(uint n){
  mgraph_p g = mgraph_random(n);
  graph_p res = graph_from_mgraph(g);
  mgraph_free(g);
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

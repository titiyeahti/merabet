/*
 * =====================================================================================
 *
 *       Filename:  graph-gen.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/01/2021 19:48:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "graph.h"

#define SIZE 9

void main(void){
  graph_p g = graph_random(9);
  graph_to_file(g, "../graphs/test");
  graph_print(g);

  graph_free(g);

  printf("coucou\n");

  g = graph_from_file("../graphs/test");
  graph_print(g);
  graph_free(g);
}

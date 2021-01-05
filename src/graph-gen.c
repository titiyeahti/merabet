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

#define POP 10

int size[6] = {20, 50, 100, 400, 600, 1000};

void main(void){
  srand(time(NULL));
  char buffer[100];
  int i;
  int j;

  for(i=0; i<6; i++){
    printf("i :%d\n", size[i]);
    for(j=0; j<POP; j++){
      sprintf(buffer, "../graphs/%d_%d", size[i], j);
      graph_p g = graph_random(size[i]);
      graph_to_file(g, buffer);
      graph_free(g);
    }
  }
}

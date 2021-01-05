/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  testing file
 *
 *        Version:  1.0
 *        Created:  05/01/2021 14:38:39
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

void main(void){
  graph_p g = graph_random(25);
  graph_print(g);

  graph_free(g);
}

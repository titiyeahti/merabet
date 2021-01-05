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
  mgraph_p g = mgraph_random(10000);
/*  graph_print(g);*/

  mgraph_free(g);
}

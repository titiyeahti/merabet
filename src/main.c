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

#include "departager.h"



void main(void){

 

  graph_p g = graph_random(25);
  graph_print(g);

  graph_free(g);

//part 2 test
  arret_p* l = create_L(5);
  int i;
  for(i =0 ;i<5 ;i++){
   afficher_arrets(l[i]);
  }
graph_p * tab =create_Foret(5);
 for(i =0 ;i<5 ;i++){
   graph_print(tab[i]);
  }
  arret_p p =departager(tab,l);
  afficher_arrets(p);
  freTree(tab,5);


  


}

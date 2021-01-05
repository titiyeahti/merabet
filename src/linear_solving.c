/*
 * =====================================================================================
 *
 *       Filename:  linear_solving.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/01/2021 20:04:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */

#include "utils.h"
#include <glpk.h>

glp_prob pb_init(graph_p g);
void pb_cleanup(glp_prob pb);

/* decl good number of cols, name then, set their kind */
void pb_cols(glp_prob pb, graph_p g);

/* decl good number of rows, name then, set their */
void pb_rows(glp_prob pb, graph_p g);

void pb_matrix(gpl_prob pb, 

glp_prob pb_init(graph_p g){
  pb = glp_create
}



int main(int argc, char** argv){
  graph_p g = graph_from_file(argv[1]);

  glp_prob pb;
  pb = glp_create_prob();
  
  int n = (int) g->n;
  int m = (int) g->vertices[n]/2;
  int nb_cols = m + 2*n*m + n;
  int nb_rows = 1 + n*m + n + m;
  int z_offset = 0;
  int x_offset = n;
  int y_offset = n+m;

  int* ia = malloc(sizeof(int)*(nb_rows+1));
  int* ja = malloc(sizeof(int)*(nb_cols+1));

  int* ra = malloc(sizeof(int)*nb_cols*nb_rows);

  glp_set_prob_name(pb, "MBVST");
  glp_set_obj_name(pb, "z");
  glp_set_obj_dir(pb, GLP_MIN);

  glp_add_cols(pb, nb_cols);
  glp_add_rowq(pb, nb_rows);

  int i;
  for(i=1; i<nb_cols+1; i++)
    glp_set_col_kind(pb, i, GLP_BV);

  return EXIT_SUCCESS;
}

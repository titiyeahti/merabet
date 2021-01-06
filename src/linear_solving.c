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

#include "graph.h"
#include <glpk.h>

glp_prob* pb_init(){
  glp_prob* pb;
  pb = glp_create_prob();
  glp_create_index(pb);
  glp_set_obj_name(pb, "f");
  glp_set_obj_dir(pb, GLP_MIN);

  return pb;
}

void pb_cleanup(glp_prob* pb){
  glp_delete_index(pb);
  glp_delete_prob(pb);
}

void pb_var_z(glp_prob* pb, graph_p g){
  int i, offset;
  char buffer[100];

  offset = glp_add_cols(pb, (int) g->n);

  for(i=offset; i<g->n+offset; i++){
    sprintf(buffer, "z%d", i-offset);
    glp_set_col_name(pb, i, buffer);
    glp_set_col_kind(pb, i, GLP_BV);
    glp_set_obj_coef(pb, i, 1.0);
  }
}

void pb_var_x(glp_prob* pb, graph_p g){
  uint i, offset, m, count;
  uint *v;
  char buffer[100];

  m = g->vertices[g->n]/2;
  offset = glp_add_cols(pb, (int) m);

  count = 0;
  for(i=0; i<g->n && count < m; i++){
    FOR_ALL_NEIGH(g, i, v){
      if (*v>i){
        sprintf(buffer, "x%d%d", i, *v);
        glp_set_col_name(pb, count + offset, buffer);
        glp_set_col_kind(pb, count + offset, GLP_BV);
        glp_set_obj_coef(pb, count + offset, 0.0);
        count ++;
      }
    }
  }
}

void pb_var_y(glp_prob* pb, graph_p g){
  uint i, j, offset, m, count;
  uint *v;
  char buffer[100];

  m = g->vertices[g->n]/2;
  offset = glp_add_cols(pb, (int) 2*m*g->n);

  count = 0;
  for(i=0; i<g->n && count < 2*m*g->n; i++){
    FOR_ALL_NEIGH(g, i, v){
      if (*v>i){
        for(j=0; j<g->n; j++){
          /* direct way */
          sprintf(buffer, "y%d%d%d", i, *v, j);
          glp_set_col_name(pb, count + offset, buffer);
          glp_set_col_kind(pb, count + offset, GLP_BV);
          glp_set_obj_coef(pb, count + offset, 0.0);
          
          /* reverse way */
          sprintf(buffer, "y%d%d%d", *v, i, j);
          glp_set_col_name(pb, count + offset + 1, buffer);
          glp_set_col_kind(pb, count + offset + 1, GLP_BV);
          glp_set_obj_coef(pb, count + offset + 1, 0.0);
          count += 2;
        }
      }
    }
  }
}

void pb_rows_a(glp_prob* pb, graph_p g){
  uint i, offset, m, x1;
  char buffer[100];
  int* ind;
  double* val;
  offset = glp_add_rows(pb, 1);

  m = g->vertices[g->n]/2;

  ind = malloc(sizeof(int)*(m+1));
  val = malloc(sizeof(double)*(m+1));

  sprintf(buffer, "x0%d", g->edges[0]);
  x1 = glp_find_col(pb, buffer);

  for(i=0; i<m; i++){
    ind[i+1] = x1 + i;
    val[i+1] = 1; 
  }

  glp_set_row_bnds(pb, (int) offset, GLP_FX, (double) (g->n - 1), 
      (double) (g->n - 1));

  glp_set_row_name(pb, (int) offset, "1a");

  glp_set_mat_row(pb, (int) offset, m, ind, val);

  free(ind);
  free(val);
}

void pb_rows_b(glp_prob* pb, graph_p g){
  uint i, j, offset, m, x1, y1, spot;
  char buffer[100];
  int* ind;
  double* val;

  m = g->vertices[g->n]/2;
  offset = glp_add_rows(pb, m*g->n);
  
  sprintf(buffer, "x0%d", g->edges[0]);
  x1 = glp_find_col(pb, buffer);
  
  sprintf(buffer, "y0%d0", g->edges[0]);
  y1 = glp_find_col(pb, buffer);

  ind = malloc(sizeof(int)*(3+1));
  val = malloc(sizeof(double)*(3+1));

  for(i=0; i<m; i++){
    for(j=0; j<g->n; j++){
      ind[1] = (int) y1 + 2*(i*g->n + j); 
      ind[2] = (int) ind[1]+1; 
      ind[3] = (int) x1+i;
      val[1] = 1.0; val[2] = 1.0; val[3] = -1.0;

      spot = offset + i*g->n + j;
      glp_set_row_bnds(pb, (int) spot, GLP_FX, 0.0, 0.0);

      sprintf(buffer, "1b%d%d", i, j);
      glp_set_row_name(pb, (int) spot, buffer);

      glp_set_mat_row(pb, (int) spot, 3, ind, val);
    }
  }

  free(ind);
  free(val);
}

void pb_rows_c(glp_prob* pb, graph_p g){
  uint i, j, offset, m, x1, y1, spot, count, count2;
  uint *v;
  char buffer[100];
  int* ind;
  double* val;

  m = g->vertices[g->n]/2;
  offset = glp_add_rows(pb, m);
  
  ind = malloc(sizeof(int)*(g->n-1+1));
  val = malloc(sizeof(double)*(g->n-1+1));
  
  count = 0;
  
  for(i=0; i<g->n && count < m; i++){
    FOR_ALL_NEIGH(g, i, v){
      if (*v>i){
        count2 = 0;
        for(j=0; j<g->n; j++){
          if(j != i && j != *v){
            sprintf(buffer, "y%d%d%d", i, j, *v);
            y1 = glp_find_col(pb, buffer);

            if(y1){
              spot = count2+1;
              ind[spot] = y1;
              val[spot] = 1.0;
              count2 ++;
            }
          }
        }
        sprintf(buffer, "x%d%d", i, *v);
        x1 = glp_find_col(pb, buffer);
        ind[count2+1] = x1;
        val[count2+1] = 1.0; 

        spot = offset + count;

        glp_set_row_bnds(pb, (int) spot, GLP_FX, 1.0, 1.0);

        sprintf(buffer, "1c%d", count);
        glp_set_row_name(pb, (int) spot, buffer);

        glp_set_mat_row(pb, (int) spot, count2+1, ind, val);

        count ++;
      }
    }
  }

  free(ind);
  free(val);
}

void pb_rows_d(glp_prob* pb, graph_p g){
  uint i, j, offset, m, x1, spot, deg;
  uint *v;
  char buffer[100];
  int* ind;
  double* val;

  m = g->vertices[g->n]/2;
  offset = glp_add_rows(pb, g->n);
  
  ind = malloc(sizeof(int)*(m+1));
  val = malloc(sizeof(double)*(m+1));
  
  for(i=0; i<g->n; i++){
    deg = DEG(g, i);
    j = 0;
    FOR_ALL_NEIGH(g, i, v){
      if(i < *v) 
        sprintf(buffer, "x%d%d", i, *v);
      else 
        sprintf(buffer, "x%d%d", *v, i);

      ind[j+1] = glp_find_col(pb, buffer);
      val[j+1] = 1.0;

      j++;
    }

    sprintf(buffer, "z%d", i);
    ind[j + 1] = glp_find_col(pb, buffer);
    val[j + 1] = (double) -deg;

    spot = offset + i;
        
    glp_set_row_bnds(pb, (int) spot, GLP_UP, 0.0, 2.0);

    sprintf(buffer, "1d%d", i);
    glp_set_row_name(pb, (int) spot, buffer);

    glp_set_mat_row(pb, (int) spot, deg+1, ind, val);
  }

  free(ind);
  free(val);
}

int main(int argc, char** argv){
  graph_p g;
  double f;
  g = graph_from_file(argv[1]);

  glp_prob* pb;
  pb = pb_init();
  
  /* cols */
  pb_var_z(pb, g);
  pb_var_x(pb, g);
  pb_var_y(pb, g);

  /* rows */
  pb_rows_a(pb, g);
  pb_rows_b(pb, g);
  pb_rows_c(pb, g);
  pb_rows_d(pb, g);

  /* SOLVING */
  clock_t t = clock();
  glp_simplex(pb, NULL);
  t = clock() - t;

  f = glp_get_obj_val(pb);

  printf("size : %d\nclock ticks : %d\nres_value : %f\n", g->n, t, f);

  pb_cleanup(pb);
  graph_free(g);
  return EXIT_SUCCESS;
}

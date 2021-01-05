/*
 * =====================================================================================
 *
 *       Filename:  utils.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  24/10/2020 11:15:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */


#ifndef  utils_INC
#define  utils_INC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef unsigned int uint;
typedef unsigned char uchar;

#define EXIT_ERROR(fct_name) \
  fprintf(stdout, "error at %s:%s:%d\n", fct_name, __FILE__, __LINE__); \
  exit(EXIT_FAILURE)

#define RAND_UINT(n) (uint) (rand() % n)

#define RAND_INT(n) (rand() % n)

#define RAND_INT_AB(a, b) (RAND_INT((b)-(a)) + (a))

#define RAND_UNIF_01 (float)((double) rand()/(double) RAND_MAX)

#define RAND_FLOAT(x, y) (float)(RAND_UNIF_01 * (y-x) + x)

#define MAX(x, y) (x) > (y) ? (x) : (y)

#define MIN(x, y) (x) > (y) ? (y) : (x)

#endif   /* ----- #ifndef utils_INC  ----- */



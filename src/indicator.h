/*
 * =====================================================================================
 *
 *       Filename:  indicator.h
 *
 *    Description:  This file defines a representation for the subsets of 
 *          [0..MAX_INT] using indicator functions. It also implements most of
 *          useful operations as macros. Since the names are quite explicit not 
 *          very much commentary.
 *
 *        Version:  1.0
 *        Created:  20/10/2020 19:42:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */


#ifndef  indicator_INC
#define  indicator_INC

#include "utils.h"

/* A subset of [0..n] is coded as following :
 *    * ind is an array of size (n/8 + 1);
 *    * i in ind <=> ind[i/8] & 2^(i % 8)*/
typedef uchar* ind_p;

#define IND_NEW(n) (ind_p) malloc((((n)>>3)+1) * sizeof(char))

#define IND_COPY(dest, src, n) memcpy(dest, src, ((n)>>3)+1)

#define IND_SET(ind, i) ind[(i)>>3] |= 1<<((i)&7)

#define IND_FLIP(ind, i) ind[(i)>>3] ^= 1<<((i)&7)

#define IND_UNSET(ind, i) (ind)[(i)>>3] &= (255^(1<<((i)&7)))

#define IND_TEST(ind, i) ((ind)[(i)>>3] & (1<<((i)&7)))

#define IND_FILL(ind, n, k) for(k=0; k<((n)>>3)+1; k++) ind[k] = 255

#define IND_CLEAR(ind, n, k) for(k=0; k<((n)>>3)+1; k++) ind[k] = 0

#define IND_CARD(ind, n, k, card) \
  card = 0; \
  for(k=0; k<(n); k++) \
    if(IND_TEST(ind, k)) card++

/* Intersection */
#define IND_AND(ind, ind1, ind2, n, k) \
  for(k=0; k<((n)>>3)+1; k++) (ind)[k] = (ind1)[k] & (ind2)[k]

/* Union */
#define IND_OR(ind, ind1, ind2, n, k) \
  for(k=0; k<((n)>>3)+1; k++) (ind)[k] = (ind1)[k] | (ind2)[k]

#define IND_XOR(ind, ind1, ind2, n, k) \
  for(k=0; k<((n)>>3)+1; k++) (ind)[k] = (ind1)[k] ^ (ind2)[k]

#define IND_FREE(ind) free(ind)

/* WARNING : n is the number of elements not the size of the array */
#define IND_PRINT(ind, n, k) \
  for(k=0; k<(n); k++) {\
    if(IND_TEST(ind, k)) printf("%d ", k);}\
  printf("\n")

#endif   /* ----- #ifndef indicator_INC  ----- */

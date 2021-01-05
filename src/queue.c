/*
 * =====================================================================================
 *
 *       Filename:  queue.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/10/2020 22:55:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */

#include "queue.h"

queue_p queue_new(uint n){
  queue_p ret = malloc(sizeof(queue_t));
  ret->top = 0;
  ret->bot = 0;
  ret->n = n;
  ret->data = malloc(n*sizeof(uint));

  return ret;
}

void queue_push(queue_p q, uint i){
  if(q->top < q->n){
    q->data[q->top] = i;
    q->top ++;
  }
  else {
    printf("queue_push : queue is full\n");
    exit(EXIT_FAILURE);
  }
}

uint queue_pop_bot(queue_p q) {
  uint res;
  
  if(QUEUE_CARD(q)){
    res = q->data[q->bot];
    q->bot ++;
    return res;
  }
  else {
    fprintf(stderr, "queue_pop_bot : queue is empty\n");
    exit(EXIT_FAILURE);
  }
}

uint queue_pop_top(queue_p q) {
  uint res;

  if(QUEUE_CARD(q)){
    q->top --;
    res = q->data[q->top];

    return res;
  }
  else {
    fprintf(stderr, "queue_pop_top : queue is empty\n");
    exit(EXIT_FAILURE);
  }
}

uint queue_pop_id(queue_p q, uint i) {
  uint res;

  if(i>=QUEUE_CARD(q)){
    EXIT_ERROR("queue_pop_id");
  }

  q->top --;
  res = q->data[q->bot + i];
  q->data[q->bot + i] = q->data[q->top];

  return res;
}

void queue_copy(queue_p dest, queue_p src){
  if(dest->n != src->n){
    EXIT_ERROR("queue_copy");
  }
  dest->top = src->top;
  dest->bot = src->bot;
  memcpy(dest->data, src->data, (src->n)*sizeof(uint));
}

void queue_print(queue_p q){
  uint i;
  for(i=q->bot; i<q->top; i++)
    printf("%d ", q->data[i]);

  printf("\n");
}

void queue_free(queue_p q){
  free(q->data);
  q->data = NULL;
  free(q);
  q = NULL;
}

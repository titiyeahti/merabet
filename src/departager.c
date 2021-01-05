
#include "departager.h"

void afficher_arrets(arret_p p){
  if(NULL != p){
    printf(" u = %d v= %d \n",p->u,p->v);
  }
}
arret_p *create_L(int n){
  nbr_couples =n;
  int i;
  arret_p* l = malloc( n *sizeof(E_t));
  for(i =0 ;i<n ;i++){
    arret_p p =  malloc(sizeof(E_t));
  p->u = RAND_UINT(30);
  p->v = RAND_UINT(50);
    l[i]  = p;
  }
  return l;
}
void freTree(graph_p * tab,int n){
int i;
for(i=0;i<n;i++){
    graph_free(tab[i]);
}
}
graph_p * create_Foret(int n){
nbr_trees = n;
  int i;
  graph_p* foret = malloc( n *sizeof(graph_t));
  for(i =0 ;i<n ;i++){

    foret[i]  = graph_random(10);
  }
  return foret;
}
bool exist(uint val ,arret_p* l ){
  int i;
  for(i = 0;i<nbr_couples;i++){
    if(l[i]->u == val || l[i]->v ==val){
      return true;
    }
  }
  return false;
}
arret_p departager( graph_p* foret, arret_p* l ){
int i,j;
for(i=0;i<nbr_trees;i++){
  int cp=0;
  uint u;
  uint v;
  uint  dT_u;
  uint dT_v;
  for(j=0;j<foret[i]->n;j++){
    dT_v =-1;
    dT_u=-1;
  if(   exist((foret[i]->vertices)[j] ,l) ){
    if(cp == 0 ){
      cp++;
      dT_u =(foret[i]->vertices)[j+1] -(foret[i]->vertices)[j];
      u=(foret[i]->vertices)[j] ;
    }else if(cp ==1){
      cp++;
      dT_v= (foret[i]->vertices)[j+1]-(foret[i]->vertices)[j];
      v =(foret[i]->vertices)[j] ;
    }
    }
  }
  if(dT_v == 1 && dT_u ==1)//en  a trouver le couplet (u,v)
  {
    arret_p p =  malloc(sizeof(E_t));
  p->u = u;
  p->v = v;
  return p;
  }else // return any of L
  {
    return l[0];
  }
  
}
return NULL;
}


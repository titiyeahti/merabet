#ifndef  departager_INC
#define  departager_INC
#include <stdlib.h>
#include "graph.h"
#include <stdbool.h>

typedef struct  E 
{
    uint u;
    uint v;
}E_t;
typedef E_t * arret_p;
int nbr_couples,nbr_trees;
void afficher_arrets(arret_p p);
arret_p *create_L(int n);
void freTree(graph_p * tab,int n);
graph_p * create_Foret(int n);
arret_p departager( graph_p* foret, arret_p* l );


#endif 
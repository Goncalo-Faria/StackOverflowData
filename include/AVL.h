#include "date.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef AVL_h
#define AVL_h


// struct da tentry , recebe como parametros uma key e dados
typedef struct tentry* TreeEntry;

/*
*balanceador da minha AVL :
*LH -> Left 
*EH -> Equilibrado
*RH -> Direita
*/
typedef enum balancefactor { LH , EH , RH } BalanceFactor;

//struct do Tree
typedef struct treenode *Tree;

//struct da AVL
typedef struct avl *AVL;

/*
*Insere um nodo na Tree
*tem um elemento cresceu caso a arvore aumente de tamanho
*/
Tree insertTree(Tree t, TreeEntry e, int *cresceu);

// cria a AVL
/*
*compare ..
..
*/
AVL create_avl ( int (*compare) (void* , void*, void* ), void (*free_key) (void *), void (*free_data) (void*) );

//insere na AVL uma determinada key e dados (TreeEntry)
AVL insertAVL (AVL a , void *key , void *dados);

//aplica uma rotacao da Tree ha esquerda
Tree rotateLeft(Tree t);

//aplica uma rotacao da Tree ha direita
Tree rotateRight(Tree t);

//Balanceia a arvore ha direita
Tree balanceRight(Tree t);

//Balanceia a arvore ha esquerda
Tree balanceLeft(Tree t)

//verifica se é AVL (tipo booleano)
int isAVL (Tree t);

//Destroi uma determinada AVL
void destroy_AVL(AVL x);


#endif /* avl_h */
//#include "date.h"
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

typedef void (*Free_function) (void *); 

typedef int (*Compare) (void * , void* , void*);

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

//numero de nodes da AVL;
int get_num_node (AVL x);

//insere na AVL uma determinada key e dados (TreeEntry)
void insertAVL (AVL a , void *key , void *dados);

//aplica uma rotacao da Tree ha esquerda
Tree rotateLeft(Tree t);

//aplica uma rotacao da Tree ha direita
Tree rotateRight(Tree t);

//Balanceia a arvore ha direita
Tree balanceRight(Tree t);

//Balanceia a arvore ha esquerda
Tree balanceLeft(Tree t);

//verifica se é AVL (tipo booleano)
int isAVL (Tree t);


int nonAVL_treeHeight(Tree t);

//Destroi uma determinada AVL
void destroy_AVL(AVL x);

void null_check (void *x , Free_function f);
/*
*Destroi uma determinada Tree , atraves de :
*f_key para destrui a chave  
*f_dados para destruir os dados 
*/
void destroy_Tree (Tree t , Free_function f_key , Free_function f_dados);


// FUNCOES PARA TESTAR SE A MINAH FUNCAO ETSA CERTOasdasdas
char balChar (BalanceFactor bal);

void dumpKeys (Tree t, int level);

Tree get_Tree (AVL x);

TreeEntry get_TE (Tree x);

Tree get_Tleft (Tree x);

Tree get_Tright (Tree x);

void* get_keyE (TreeEntry x);

void* get_dadosE (TreeEntry x);

#endif /* avl_h */
//#include "date.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef AVL_h
#define AVL_h



typedef struct tentry* TreeEntry;

typedef enum balancefactor { LH , EH , RH } BalanceFactor;

typedef struct treenode *Tree;

typedef struct avl *AVL;

Tree insertTree(Tree t, TreeEntry e, int *cresceu);

int isAVL (Tree t);




#endif /* avl_h */
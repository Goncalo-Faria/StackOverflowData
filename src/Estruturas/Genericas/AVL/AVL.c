#include <stdio.h>
#include "AVL.h"



void null_check (void *x , Free_function f){
    if (x) f(x);
}

typedef void (*Free_function) (void *); 
typedef int (*Compare) (void * , void* , void*);


typedef struct treenode {
    BalanceFactor bf;
    TreeEntry entry;
    void* key;
    struct treenode *left;
    struct treenode *right;
}*Tree;

typedef struct tentry{
    void* key;
    void* dados;
}* TreeEntry;


typedef struct avl {
    Tree root;
    unsigned int num_node;
    Compare compare; 
    Free_function free_key; // if null don't use .
    Free_function free_dados; // if null don't use.

}*AVL;

      

AVL create_avl ( int (*compare) (void* , void*, void* ), void (*free_key) (void *), void (*free_dados) (void*) ) {
    
    AVL x = malloc( sizeof(struct avl) );
    x->root = NULL;
    x->free_dados= free_dados;
    x->free_key= free_key;
    x->num_node=0;
    x->compare = compare; 
    return x;
}


/*Numa determinada AVL 
* Temos uma certa key e dados e fazemos uma tentry
* Mete-mos a determinada tentry na Tree 
* InsertTree insere um determinado nodo como tambem diz se a arvore cresceu ou nao
*/
AVL insertAVL (AVL a , void *key , void *dados){
    TreeEntry t = malloc (sizeof (struct tentry));
    t->key = key;
    t->dados = dados;
    Tree x = a->root;
    int cresceu = 0;
    insertTree (x , t , &cresceu);
    free (t);
    a->num_node++;
    return a;

}


int get_num_node (AVL x){
    return (x->num_node);
}  

/*
Tree create_tree(void){
    Tree t = malloc (sizeof (struct treenode));
    t->bf = EH;
    t->entry = 0;
    t->key = NULL;
    t->date = NULL;
}
*/
void destroy_AVL(AVL x){
    Free_function f_key = x->free_key;
    Free_function f_dados = x->free_dados;
    Tree t = x->root;
    if(t) {
        destroy_Tree(t,f_key,f_dados); 
    }
        free(t);
        null_check (x,free);
    
}




void destroy_Tree (Tree t , Free_function f_key , Free_function f_dados){
    if(t){
         if (t->entry->key){
              null_check ( t->entry->key ,f_key );
              null_check ( t->entry->dados , f_dados);
              free (t->entry); 
          }
    destroy_Tree (t->left,f_key,f_dados);
    destroy_Tree (t->left,f_key,f_dados);
     }
}   


Tree rotateLeft(Tree t)
{
    Tree aux = t->right;
    t->right = aux->left;
    aux->left = t;
    t = aux;
    return t;
}

Tree rotateRight(Tree t){
    Tree aux = t->left;
    t->left = aux -> right;
    aux->right = t;
    return t;
}


Tree balanceRight(Tree t)
{
    if (t->right->bf==RH) {
        // Rotacao simples a esquerda
        t = rotateLeft(t);
        t->bf = EH;
        t->left->bf = EH;
    }
    else {
        //Dupla rotacao
        t->right = rotateRight(t->right);
        t=rotateLeft(t);
        switch (t->bf) {
            case EH:
                t->left->bf = EH;
                t->right->bf = EH;
                break;
            case LH:
                t->left->bf = EH;
                t->right->bf = RH;
                break;
            case RH:
                t->left->bf = LH;
                t->right->bf = EH;
        }
        t->bf = EH;
    }
    return t;
}


Tree balanceLeft(Tree t)
{
    if (t->left->bf==LH) {
        // Rotacao simples a direita
        t = rotateRight(t);
        t->bf = EH;
        t->right->bf = EH;
    }
    else {
        //Dupla rotacao
        t->left = rotateLeft(t->left);
        t=rotateRight(t);
        switch (t->bf) {
            case EH:
                t->left->bf = EH;
                t->right->bf = EH;
                break;
            case LH:
                t->left->bf = EH;
                t->right->bf = RH;
                break;
            case RH:
                t->left->bf = EH;
                t->right->bf = RH;
        }
        t->bf = EH;
    }
    return t;
    
}



//Acrescenta me um nodo, tambem diz se a arvore cresceu ou nao (pode ser util)
Tree insertTree(Tree t, TreeEntry e, int *cresceu)
{
    if (t==NULL){
        t = (Tree)malloc(sizeof(struct treenode));
        t->entry = e;
        t->right = t->left = NULL;
        t->bf = EH;
        *cresceu = 1;
    }
    else if (e > t->entry) {
        t->right=insertTree(t->right, e, cresceu);
        if (*cresceu) {
            switch (t->bf) {
                case LH:
                    t->bf = EH;
                    *cresceu = 0;
                    break;
                case EH:
                    t->bf = RH;
                    *cresceu = 1;
                    break;
                case RH:
                    t=balanceRight(t);
                    *cresceu = 0;
            }
        }
    }
    // igual ao modulo direito
    else {
        t->left=insertTree(t->left, e ,cresceu);
        if (*cresceu) {
            switch (t->bf) {
                case RH:
                    t->bf = EH;
                    *cresceu = 0;
                    break;
                case EH:
                    t->bf = RH;
                    *cresceu = 1;
                    break;
                case LH:
                    t=balanceLeft(t);
                    *cresceu = 0;
            }
        }       
    }
    return t;
}


int isAVL (Tree t) {
    int l, r;
    if (t == NULL) return 1;
    
    l = nonAVL_treeHeight (t->left);
    r = nonAVL_treeHeight (t->right);
    
    return (abs (l-r) <= 1 &&
            isAVL(t->left) &&
            isAVL(t->right));
}

int nonAVL_treeHeight(Tree t) {
    int l, r;
    
    if (t==NULL)
        return 0;
    
    l = nonAVL_treeHeight(t->left);
    r = nonAVL_treeHeight(t->right);
    if (l>r)
        return l+1;
    else return r+1;
    
}
  



/*

int treeHeight(Tree t) {

    // Falta fazer se for preciso

}

*/







#include <stdlib.h>
#include "linkedLL.h"
/* 

    Implementação de uma lista ligada genérica.
*/

// Estrutura de dados

typedef struct node {
    void * data;
    size_t fat;
    struct node * next;
} *Node;

typedef struct root {
    Node root;
    int len;
} *LL ;

// Métodos

LL create_ll(void) {
    /*
        Esta função cria a lista.     

        0(1)
    */
    LL l = (LL)malloc( sizeof(struct root) );
    l->root=NULL;
    l->len=0;
    return l;
}

int empty_ll( LL x ) {
    /*
        1 if the linked list is empty.
        
        0(1)
    */
    return ( x->root == NULL);
}

void* ind_ll( LL x , int i, size_t * s ) {
    Node y ;
    int j=0;

    for( y= x->root ; y != NULL && j< i ; y= y->next )
        j++; 

    if ( !y ){
        return NULL;
        *s = -1;
    }

    *s = y->fat;
    
    return y->data;
}

int length_ll( LL x ) {
    /*
        Returns the length of the linked list.

    */
    return x->len ;
}

static void add_f(LL x , void* info, size_t fat ){
    /*
        Esta função cria um novo nodo.

        0(1)
    */

    Node new;
    int i;

    
    new = (Node) malloc( sizeof(struct node) );
    new->data = malloc(fat);
    new->next = x->root;
    new->fat = fat;

    // passar byte a byte
    for (i=0; i<fat; i++)
        *(char *)(new->data + i) = *(char *)(info + i);

    x->root = new;

}

int rem_N( int (*f )(void* , void*) ,LL x ,void* op1 ) {
    /*
        Esta função remove o elemento cu

        O(n)

        if f ( op1 , op2 ) == 1 :
            remove. 
    */

    void *op2;
    Node current, bf ;
    int s=0;

    if( !empty_ll(x) )
    {
        for(current = bf = x->root; current != NULL; current=current->next )
        {

            op2= current->data;

            if( f(op1,op2) )
            {
                bf->next= current->next;
                free(current->data); // faz free da capsula que agrega os dados. 
                free(current); 
                current = bf;
                x->len--;
                s=1;
            } 

            bf = current;

        }    
    }

    return s;
}

static int yes( void* a,void *b){
    /*
        auxiliary function.
        f(x)=True;    
    */
    return 1;
}

void clean_ll(LL x){
    /*
    Deletes the list. Assumes the list exists even if empty.
    */
    
    rem_N( yes, x , NULL );
    free(x); 
}


void print_ll(LL x, void (*show)(void *))
{
    /*
        Assumes the list exists even if empty.    
    */
    Node use;
    use = x->root;

    while (use != NULL)
    {
        show(use->data);
        use = use->next;
    } 
}


// reboot.
int add_N( int (*ord )(void* , void*) ,LL x ,void* op1 , size_t fat ) {
    /*
        Esta função adiciona um elemento quando a função ord é -1. 

        -> e seja ord ( a , b );

        -> é suposto ord ==1 se a >b
        -> é suposto ord == 0 se a=b
        -> é suposto ord == -1 se a<b

        . Era bom que ord fosse reflexiva, trasistiva e anti-simétrica.

        . No entanto ninguém vai chorar se isso acontecer.

    */

    void *op2;
    Node current , bf ;
    int s=0, j=0;
    struct root tmp;
    
    for(current = bf = x->root; current != NULL && !s ; current=current->next )
    {
        // enquanto é diferente de null e não foi adicionado.
        op2= current->data;
        tmp.root = current; 
        if( ord(op1,op2)<1 )
        {
            tmp.root = current;
            add_f(&tmp, op1, fat );
            s=1;
            if ( !j)
                x->root = tmp.root;
            else 
                bf->next = tmp.root;    
        }   

        j++;
        bf = current; 
    }    

    if(!s ){
        // adicionar à cuada.
        tmp.root = current; // NULL;
        add_f(&tmp, op1, fat );
        s=1;
        if ( !j)
                x->root = tmp.root;
        else 
                bf->next = tmp.root; 
    }
    x->len ++;
    return s;
}


void fmap_ll( void (*f) (void*, void*) , LL x, void* op1 ){

    /*
        Esta função remove o elemento cu

        O(n)

        if f ( op1 , op2 ) == 1 :
            remove. 
    */

    Node current ;
    for(current = x->root; current != NULL; current=current->next )
    {
            f(op1,current->data);         
    }

}

void* search_ll( int (*eq) (void*, void*), LL x, void* op1 ){
    Node aux;

    for ( aux = x->root; aux != NULL; aux = aux->next )
        if( eq( op1, aux->data ) )
            return aux->data;
    

    return NULL;
}
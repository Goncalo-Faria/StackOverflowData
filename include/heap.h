#ifndef HEAP_H
#define HEAP_H


#define pai(i) (i-1) / 2
#define esq(i) 2*i + 1
#define dir(i) 2*i + 2

typedef struct heap *HEAP; 

HEAP create_H(void (*in_free) (void*) );
/*
    Esta função cria uma nova instância da Estrutura.
*/
HEAP limcreate_H(int lim, void (*in_free) (void*) );
/*
    Esta função cria uma estrutura com um limite de elementos.
*/

void destroy_H(HEAP x);
/*
    Esta função destroi a estrutura sem perturbar os dados no caso de memória dinâmica.
*/
void destroyC_H(HEAP x,  void (*ff) (void*));
/*
    Esta função de destroi a estrutra mas antes aplica a função que recebe como input a todos os dados.

    Se receber ff == NULL é basicamente o destroy_H();
*/
int empty_H(HEAP x);
/*
    Indica 1 se a heap estiver vazia e 0 caso contrário.
*/

int length_H(HEAP x);
/*
    Indica o numero de elementos na estrutura.
*/
int maxQ_H(HEAP x);
/*
    Esta função indica se a estrutura já atingiu a capacidade inicialmente definida.
        Na eventualidade de não ter sido inserida uma capacidade devolve false.

*/

void add_Heap( HEAP x, int key , void* n);
/*
    Adiciona um elemento a heap.

*/
void addR_Heap( HEAP x, int key , void* n );
/*
    Substitui o maior elemento da heap pelo inserido.

        Caso ff seja diferente de null aplica a função aos dados.
*/
void* rem_Heap( HEAP x, int *key);
/*
    Esta função remove o elemento que está no topo da HEAP.
    
*/

#endif
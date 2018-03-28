#ifndef bArray_h
#define bArray_h

#include "heap.h"

typedef void (*freeFunc)(void *);
/*
    Dados.
*/
typedef int (*filterFunc)(void *, void *);
/*
    Dados /->userdata 
*/
typedef void (*appFunc)(void *, void *);
/*
    Dados /->userdata 
*/
typedef int (*cmpFunc)(void *, void *, void *);
/*
    Compare function.
*/

typedef struct brray *bArray;

//cria um bArray e devolve-o
bArray init_A(unsigned long n, freeFunc dados);

//destroi um determinado bArray
void destroy_A(bArray x);

//adiciona um elemento no bArray e devolve o bArray
bArray add_to_A(bArray x, void *ele);

//ordena um determinado bArray através de um funcao dada e devolve o bArray
bArray sort_A(bArray x, int (*cmp)(const void *, const void *));

//devolve o elemento de uma posicao do bArray
void *get_atA(bArray b, unsigned long i);

//verifica se o bArray esta cheia
int is_full(bArray x);

//devolve me o tamanho do bArray
unsigned long length_A(bArray x);

//percorre o bArray entre 2 dados fornecidos 
void *for_each_from_to(bArray x, void *begin, void *end, appFunc functor, cmpFunc alt_cmp, void *user_data);

//percorre todo o bArray
void *for_each(bArray x, appFunc functor, void *user_data);

//void *for_each_rev(bArray x, filterFunc functor, void *user_data);

HEAP Generalized_Priority_Queue(bArray ll, unsigned long Qsize, cmpFunc q_cmp, filterFunc functor, void *user_data);


HEAP from_to_Priority_Queue(bArray x, void *begin, void *end, unsigned long Qsize, cmpFunc q_cmp, cmpFunc ord, filterFunc functor, void *user_data);

/*
exemplo de como fazer a função de comparar para o sort ->
    se as entradas são do tipo. (int*)

static int int_cmp(const void *a, const void *b)
{

    int *an = *(int **)a; // esta linha contêm 3 asteriscos *<_>*
    int *bn = *(int **)b;

    return (*bn - *an);
}

*/

#endif
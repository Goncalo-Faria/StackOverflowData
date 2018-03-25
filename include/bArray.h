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

bArray init_A(unsigned long n, freeFunc dados);
bArray add_to_A(bArray x, void *ele);
void destroy_A(bArray x);
bArray sort_A(bArray x, int (*cmp)(const void *, const void *));

void* get_atA( bArray b, unsigned long i);
int is_full(bArray x);
unsigned long length_A(bArray x);

void* for_each_from_to(bArray x, void *begin, void *end,
                      appFunc functor,
                      cmpFunc alt_cmp,
                      void *user_data);

void* for_each(bArray x, appFunc functor, void *user_data);

void* for_each_rev(bArray x, filterFunc functor, void *user_data);

HEAP Generalized_Priority_Queue(bArray ll, unsigned long Qsize,
                                cmpFunc q_cmp,
                                filterFunc functor,
                                void *user_data);

HEAP from_to_Priority_Queue(bArray x, void *begin, void *end,
                            unsigned long Qsize,
                            cmpFunc q_cmp,
                            cmpFunc ord,
                            filterFunc functor,
                            void *user_data);

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
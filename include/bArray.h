#ifndef bArray_h
#define bArray_h

#include "heap.h"

typedef void (*freeFunc)(void*);
/*
    Dados.
*/
typedef int (*appFunc)(void*, void*);
/*
    Dados /->userdata 
*/
typedef int (*cmpFunc)(void*, void*,void*);
/*
    Compare function.
*/

typedef struct brray *bArray;

bArray init_A(unsigned long n, freeFunc dados, cmpFunc compare, void* user_data);
int add_to_A(bArray x , void* ele );
void destroy_A( bArray x);
void sort_A( bArray x);
void for_each_from_to ( bArray x , void* begin , void* end, appFunc functor, void * user_data );
void for_each( bArray x ,  appFunc functor, void * user_data );
BEAP Generalized_Priority_Queue( bArray ll, unsigned long Qsize, cmpFunc alt_cmp);
BEAP from_to_Priority_Queue ( bArray x , void* begin , void* end, unsigned long Qsize, cmpFunc alt_cmp);


#endif
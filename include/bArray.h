#ifndef bArray_h
#define bArray_h



typedef void (*freeFunc)(void*);
/*
    Dados.
*/
typedef void (*appFunc)(void*, void*);
/*
    Dados /->userdata 
*/
typedef void (*cmpFunc)(void*, void*,void*);
/*
    Compare function.
*/

typedef struct brray *bArray;

bArray init_A(unsigned long n, freeFunc dados, cmpFunc compare);

void destroy_A( bArray x );

int add_to_A(bArray x, void* ele );

void sort_A( bArray x);

corner_A(bArray x, void* from, void* to, appFunc f );

bArray init_A(unsigned long n, freeFunc dados, cmpFunc compare);

int add_to_A(bArray x , void* ele );

void destroy_A( bArray x);

corner_A(bArray x, void* from, void* to, appFunc f );

void subspace_A ( bArray x , appFunc y ,void* begin , void* end , void* user_data);

void sort_A( bArray x);



#endif
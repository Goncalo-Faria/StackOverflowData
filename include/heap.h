#ifndef HEAP_H
#define HEAP_H


#define pai(i) (i-1) / 2
#define esq(i) 2*i + 1
#define dir(i) 2*i + 2

typedef struct heap *HEAP; 

HEAP create_H(void);
HEAP limcreate_H(int lim);

void destroy_H(HEAP x);
void destroyC_H(HEAP x,  void (*ff) (void*))

int length_H(HEAP x);
int maxQ_H(HEAP x);

void add_Heap( HEAP x, int key , void* n);
void addR_Heap( HEAP x, int key , void* n , void (*ff) (void*) );
void* rem_Heap( HEAP x, int *key);

#endif
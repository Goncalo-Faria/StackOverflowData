#ifndef HEAP_H
#define HEAP_H

//#include <stdlib.h>

#define pai(i) (i-1) / 2
#define esq(i) 2*i + 1
#define dir(i) 2*i + 2

typedef struct heap *HEAP; 

HEAP create_H(void);
void destroy_H(HEAP x);
int length_H(HEAP x);

void add_Heap( HEAP x, int key , void* n , unsigned long fat);
void* rem_Heap( HEAP x, int *key, unsigned long *fat );

#endif
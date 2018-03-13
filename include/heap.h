#ifndef HEAP_H
#define HEAP_H

#define pai(i) (i-1) / 2
#define esq(i) 2*i + 1
#define dir(i) 2*i + 2

typedef void (*freeFunc)(void*);
typedef void* ENTRY;

typedef int (*Fcompare)(void*, void*, void*);
// negative value if a < b ; zero if a = b ; positive value if a > b
/*
typedef struct ent {
    
    unsigned long key;
    void * data;

} *ENTRY ;
*/

typedef struct heap * HEAP;

int empty_H(HEAP x);

unsigned long length_H(HEAP x);

HEAP create_H( freeFunc in_free , Fcompare ff , void* usr_d );

/*
HEAP limcreate_H(unsigned long lim, void (*in_free) (void*) ){
    HEAP x = (HEAP)malloc( 2 * sizeof (ENTRY) );
    x->len = 2;
    x->max = lim;
    x->dataCl = in_free;
    
    return x;
}
*/

void destroy_H(HEAP x);

ENTRY* getDestroy_H ( HEAP x , unsigned long * size);

void add_Heap( HEAP x, void* n );

void* rem_Heap( HEAP x);


HEAP heapify_H( ENTRY * v , unsigned long n , Fcompare h, void* usr_d );

#endif
#ifndef HEAP_H
#define HEAP_H


#define pai(i) (i-1) / 2
#define esq(i) 2*i + 1
#define dir(i) 2*i + 2

typedef void (*freeFunc)(void*);
typedef void* ENTRY;
typedef int (*Fcompare)(void*, void*, void*);

// negative value if a < b ; zero if a = b ; positive value if a > b


typedef struct heap * HEAP;

// Max heap.

HEAP create_H( freeFunc in_free , Fcompare ff , void* usr_d );
HEAP create_fixed_H( ENTRY * v , unsigned long n ,freeFunc in_free ,Fcompare h, void* usr_d );
void destroy_H(HEAP x);
ENTRY* getDestroy_H ( HEAP x , unsigned long * size);

void add_Heap( HEAP x, void* n );
void* rem_Heap( HEAP x);
void add_in_Place_H( HEAP x, void* n);

HEAP heapify_H( ENTRY * v , unsigned long n , Fcompare h, void* usr_d );
int empty_H(HEAP x);
unsigned long length_H(HEAP x);


typedef struct beap * BEAP;

BEAP create_B( unsigned long N , freeFunc in_free , Fcompare ff, ENTRY* g , void* usr_d );
void destroy_B(BEAP x);

void* rem_Beap( BEAP x);
void addInplace_Beap( BEAP x , void *n );

int empty_B(BEAP x);
unsigned long length_B(BEAP x);
unsigned long Capacity_B(BEAP x);

#endif
#ifndef HEAP_H
#define HEAP_H

#define pai(i) (i - 1) / 2
#define esq(i) 2 * i + 1
#define dir(i) 2 * i + 2

typedef void (*freeFunc)(void *);
typedef void *ENTRY;
typedef int (*Fcompare)(void *, void *, void *);

// negative value if a < b ; zero if a = b ; positive value if a > b

#define add_in_Place_H(x, n) add_in_Place_H_signal(x, n, NULL);

typedef struct heap *HEAP;

// Max heap.

//cria uma heap e devolve a heap
HEAP create_H(freeFunc in_free, Fcompare ff, void *usr_d);

//cria uma heap fixa e devolve a heap
HEAP create_fixed_H(ENTRY *v, unsigned long n, freeFunc in_free, Fcompare h, void *usr_d);

//destroi uma especifica heap
void destroy_H(HEAP x);

//adiciona um elemento na heap e devolve a heap
HEAP add_Heap(HEAP x, void *n);

//removemos uma determinada heap
void *rem_Heap(HEAP x);

//adiciona um elemento na heap e devolve a heap
HEAP add_in_Place_H_signal(HEAP x, void *n, int *flag);

void *get_root_point(HEAP x);

//verifica se a heap esta vazia
int empty_H(HEAP x);

//devolve o tamanho da heap
unsigned long length_H(HEAP x);

#endif
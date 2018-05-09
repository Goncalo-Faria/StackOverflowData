#ifndef HEAP_H
#define HEAP_H

typedef void *ENTRY;

typedef struct heap *HEAP;

typedef void (*freeFunc)(void *);
/*
    Dados.
*/

typedef int (*Fcompare)(void *, void *, void *);
/*
    Compare function.
*/

// negative value if a < b ; zero if a = b ; positive value if a > b

#define add_in_Place_H(x, n) add_in_Place_H_signal(x, n, NULL);

// Max heap.

/**
*Recebe um funcao para dar free aos elementos e uma funcao de comparação  e um data
*Cria a heap e atualiza a estrutura com estas funcoes
*Devolve a heap
*/
HEAP create_H(freeFunc in_free, Fcompare ff, void *usr_d);

/**
*Faz o mesmo que a create_H mas esta funcao tem tamanho fixo ou seja o tamanho da heap e os usados serao iguais ao n que recebemos
*Devolve a Heap
*/
HEAP create_fixed_H(ENTRY *v, unsigned long n, freeFunc in_free, Fcompare h, void *usr_d);

/**
*Destroi um especifica Heap e apaga-a da memoria
*/
void destroy_H(HEAP x);

/**
*Adiciona um elemento na heap 
*Devolve a Heap
*/
HEAP add_Heap(HEAP x, void *n);


/**
*Remove o primeiro elemento da Heap caso a heap seja diferente de Null , de seguida troca-o com o ultimo elemento e aplica o algoritmo Bubbledown pois é uma MaxHeap
*Devolve o primeiro elemento removido
*/
void *rem_Heap(HEAP x);

/**
*Devolve o primeiro elemento da Heap
*/
void *get_root_point(HEAP x);

/**
*Devolve um int :
	1 se a Heap estiver vazio
	0 se a Heap nao estiver vazia
*/
int empty_H(HEAP x);

/**
*Devolve um long contendo o tamanho da Heap
*/
unsigned long length_H(HEAP x);


/**
*
*/
HEAP add_in_Place_H_signal(HEAP x, void *n, int *flag);

#endif
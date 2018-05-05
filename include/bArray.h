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

/**
*Estrutura de um brray(array) nomeada bArray
*/
typedef struct brray *bArray;

/**
*Recebe um long contendo o tamanho do bArray e uma funcao que faz free aos dados
*Cria um bArray , ao criá-lo associa a funcao dados na sua estrtura e devolve o bArray
*/
bArray init_A(unsigned long n, freeFunc dados);

/**
*Destroi um bArray e apaga-o da memoria
*/
void destroy_A(bArray x);

/**
*Adiciona um elemento no bArray 
*Devolve o bArry
*/
bArray add_to_A(bArray x, void *ele);

/**
*Rescebe como argumentos um bArray e uma funcao de comparacao 
*Ordena o bArray atraves da funcao , alterando a variavel ord do bArray
* ord está 0 quando o array ainda nao foi ordenado , como estas a passar esta funcao mudamos ord para 1
*Devolve o bArray
*/
bArray sort_A(bArray x, int (*cmp)(const void *, const void *));

/**
*Devolve um elemento do bArray de uma posicao dada 
*/
void *get_atA(bArray b, unsigned long i);

/**
*Verifica se o bArray esta cheio:
 Devolve 1 se estiver cheio
 Devolve 0 se nao estiver
*/
int is_full(bArray x);

/**
*Devolve um long contendo o tamanho do bArray
*/
unsigned long length_A(bArray x);

//percorre o bArray entre 2 dados fornecidos 
/**
*Recebe como argumentos um bArray , um inicio , um fim , uma funcao x , uma funcao de comparacao e um data
*Aplica a funcao x a todos os elementos do bArray entre um inicio e um fim alterando o userdata, se o bArray estiver ordenado pois é uma pesquisa binaria
*Devolve o data
*/
void *for_each_from_to(bArray x, void *begin, void *end, appFunc functor, cmpFunc alt_cmp, void *user_data);

/**
*Faz o mesmo que o for_each_from_to mas para o bArray todo
*/
void *for_each(bArray x, appFunc functor, void *user_data);

/**
*Recebe um bArray , uma funcao filter e um data
*Percorre o bArray alterando o data atraves do functor
*Devolve o data
*/
void *for_each_rev(bArray x, filterFunc functor, void *user_data);



/**
 * 
 *Cria uma Heap a partir de uma Lista  e respetivas funcoes
 * */
HEAP Generalized_Priority_Queue(bArray ll, unsigned long Qsize, cmpFunc q_cmp, filterFunc functor, void *user_data);

/**
 * Faz o mesmo que o Generalized_Priority_Queue mas entre duas Datas
 * */
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
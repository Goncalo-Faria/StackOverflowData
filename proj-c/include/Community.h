#ifndef community_h
#define community_h

#include "interface.h"
#include "Publicacao.h"
#include "Utilizador.h"
#include "heap.h"


/**
*Estrutura base para community
*/
typedef struct TCD_community *TAD_community;

typedef int (*Fcompare)(void *, void *, void *);
/*
    Compare function.
*/

//cria e devolve uma estrutura de community
/**
*Cria um TAD_community
*Devolve um TAD_community
*/
TAD_community init(void);

/**
*Destroi um TAD_community
*/
TAD_community clean(TAD_community com);

/**
*Ativa um TAD_community 
*Devolve um TAD_community
*/
TAD_community activate(TAD_community com);

/**
*Cria um respetivo bArray com n elementos 
*Devolve o TAD_community
*/
TAD_community turnOn_array(TAD_community com, unsigned long n);

/**
*Ordena o bArray do TAD_community 
*Devolve o TAD_community
*/
TAD_community finalize_array(TAD_community com);

/**
*Adiciona uma tag na g_hash_table tagconv do TAD_community
*Devolve o TAD_community
*/
TAD_community assign_tag(TAD_community com, char *key, unsigned int code);


/**
*  Verifica se palavra recebida está no conjunto de tags. 
*/
int contains_tag(TAD_community com, char *word);

/**
*Adiciona um Utilizador na g_hash_table userbyId do TAD_community
*Devolve o TAD_community
*/
TAD_community userSet_insert_id(TAD_community com, unsigned long *key, Util x);

/**
*Adiciona uma Publicacao na g_hash_table post do TAD_community
*Devolve o TAD_community
*/
TAD_community postSet_insert(TAD_community com, unsigned long *key, Post x);

/**
*Adiciona uma Publicacao no bArray postArray do TAD_community
*Devolve o TAD_community
*/
TAD_community insert_array(TAD_community com, Post x);


/**
*Procura e devolve um Utilizador na g_hash_table userByid do TAD_community
*/
Util userSet_id_lookup(TAD_community com, unsigned long num);

/**
*Procura e devolve uma Publicacao na g_hash_table post do TAD_community
*/
Post postSet_lookup(TAD_community com, unsigned long num);

/**
*Devolve um int contendo o tamanho da g_hashtable de userByid do TAD_community
*/
unsigned int userSet_size(TAD_community com);

/**
*Devolve um int contendo o tamanho da g_hashtable de post do TAD_community
*/
unsigned int postSet_size(TAD_community com);

/**
*Devolve um int :
  1 se o TAD_community esta ativado
  0 se o TAD_community nao esta ativado
*/
int is_ON(TAD_community com);

/**
*Recebe como argumento um TAD_community e uma tag
*Funcao procura se a tag está contida na g_has_table tagconv do TAD_community e se estiver devolve o numero da tag(convertido) em binario
*/
unsigned int code_tag(TAD_community com, char *word);

/**
*Recebe como argumentos um TAD_community, um inicio , um fim , uma funcao x e um data
*Percorre o bArray entre o inicio e o fim e aplica a funcao aos elementos e ao data , alterando o data
*Devolve o data
*/
void *arraySeg_transversal(TAD_community com, Date begin, Date end, void (*functor)(void *, void *), void *user_data);

/**
*Faz o mesmo que a funcao em cima mas para todo o bArray da TAD_community
*/
void *arrayRev_transversal(TAD_community com, int (*functor)(void *, void *), void *user_data);

/**
*Recebe como argumentos um TAD_community , uma determinada funcao e um data
*Percorre a g_hash_table post através da funcao e guarda o resultado em data
*Devolve o data
*/
void *postSet_transversal(TAD_community com, void (*f)(void *, void *, void *), void *x);

/**
*Recebe como argumentos um TAD_community , uma determinada funcao e um data
*Percorre a g_hash_table userbyId através da funcao e guarda o resultado em data
*Devolve o data
*/
void *userSet_id_transversal(TAD_community com, void (*f)(void *, void *, void *), void *x);

/*
*Percorre o bArray transformando-o numa heap(max Heap) atraves de funcoes dadas e devolve a Heap
*/
HEAP array_Priority_Queue(TAD_community com, unsigned long Qsize, Fcompare q_cmp, int (*filter)(void *, void *), void *user_data);

/*
*Faz praticamente o mesmo que a funcao defenida em cima mas entre dois argumenots
*/
HEAP arraySeg_Priority_Queue(TAD_community com, Date begin, Date end,unsigned long Qsize,Fcompare q_cmp,int (*filter)(void *, void *), void *user_data);

#endif
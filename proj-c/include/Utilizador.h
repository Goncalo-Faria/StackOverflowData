#ifndef utilizador_h
#define utilizador_h

#include "date.h"
#include "Publicacao.h"

/**
*Estrutura de um Utilizador nomeada por Util
*/
typedef struct utilizador *Util;

#define Q_belongs_hash(user, id) belongs_toBacia(user, id, 1)
#define A_belongs_hash(user, id) belongs_toBacia(user, id, 2)

/**
*Cria um novo Utilizador
*Devolve o Utilizador
*/
Util createUtil();

/**
*Aceita como parametro um determinado Utilizador
*Destroi o Utilizador e apago-o da memoria 
*/
void destroyUtil(void *x);

//void setDate ( Post x ,int d,int m ,int a);

// User getters ------------------------------------------------------------------

/**
*Aceita como parametro um Utilizador
*Devolve o Id associado a esse Utilizador
*/
unsigned long getU_id(Util x);

/**
*Devolve o pointer para o Id do Utilizador
*/
unsigned long *getU_id_point(Util x);

/**
*Devolve um int contendo o numero de perguntas de um Utilizador
*/
unsigned int getU_Q(Util x);

/**
*Devolve um int contendo o numero de respostas de um Utilizador
*/
unsigned int getU_A(Util x);

/**
*Devolve uma String contendo o nome de um Utilizador
*/
unsigned char *getU_name(Util x);
// alloca memoria

/**
*Devolve um pointer contendo o nome de um Utilizador
*/
unsigned char *getU_name_point(Util x);

/**
*Devolve uma String contendo a biografia de um Utilizador
*/
unsigned char *getU_bio(Util x);
//alloc memoria

/**
*Devolve um int contendo a reputacao de um Utilizador
*/
int getU_rep(Util x);

//Util setters -----------------------------------------------------------------

/**
*Atualiza o numero de perguntas de um Utilizador incrementando uma unidade
*Devolve o utilizador
*/
Util incU_Q(Util x);

/**
*Atualiza o numero de respostas de um Utilizador incrementando uma unidade
*Devolve o utilizador
*/
Util incU_A(Util x);

/**
*Atualiza o Id de um Utilizador
*Devolve o Utilizador
*/
Util setU_id(Util x, unsigned long num);

/**
*Atualiza o nome de um Utilizador 
*Devolve o Utilizador
*/
Util setU_name(Util x, const unsigned char *un);

/**
*Atualiza a biografia de um Utilizador
*Devolve o Utilizador
*/
Util setU_bio(Util x, const unsigned char *un);

/**
*Recebe como argumentos um Utilizador , um Id e dados
*Adiciona na bacia(g_hashtable) a informacao 
*Devolve um Utilizador
*/
Util add_toBacia(Util x, unsigned long *id, void *dados);

/**
*Atualiza a reputacao de um Utlizador
*Devolve o Utilizador
*/
Util setU_rep(Util x, int n);

//Functions --------------------------------------------------------------------

//Util add_toBacia(Util x, unsigned int *id, void *dados);

/**
*Funcao que recebe como argumentos um User , um long e uma flag(resposta ou pregunta)
*Devolve um int :
 1 se for pergunta e pertencer ha bacia do Utilizador
 2 se for resposta e pertencer ha bacia do Utilizador
*/
int belongs_toBacia(Util x, unsigned long Parent_id, char flag);

/**
*Funcao que recebe como argumentos um Utilizador , uma funcao e um data
*Percorre a bacia do respetivo Utilizador , aplica a funcao a cada elemento alterando o data(de acordo com a funcao)
*Devolve o data
*/
void* toBacia_transversal(Util x, void (*f)(void *, void *, void *), void *y);

/**
*Procura o respetivo Parent_id na bacia do Utilizador
*Devolve o long do respetivo Parent_id se existir , caso contrario devolve NULL
*/
unsigned long *toBacia_lookup(Util x, unsigned long Parent_id);

/**
*Devolve o tamanho da bacia
*/
unsigned int toBacia_size( Util x);

/**
*Devolve um int que representao um bollean
	1 se a key pertencer ha bacia do Utilizador
	0 se a key nao pertencer
*/
int toBacia_contains(Util x, unsigned long key);

/**
*Caso seja pergunta verificamos se o id do Post pertence ha bacia , caso nao pertenca adicionamos , key é null.
*Caso for uma resposta e o parent id do Post pertencer a bacia removemos e adicionamos ha respetiva bacia o atual em que a key é o id da resposta
*/
Util bind_toBacia(Util x, Post y);

#endif
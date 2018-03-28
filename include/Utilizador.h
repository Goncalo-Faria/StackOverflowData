#ifndef utilizador_h
#define utilizador_h

#include "date.h"
#include "Publicacao.h"

typedef struct utilizador *Util;

#define Q_belongs_hash(user, id) belongs_toBacia(user, id, 1)
#define A_belongs_hash(user, id) belongs_toBacia(user, id, 2)

//cria e devolve um util
Util createUtil();

//destoi um especifico post
void destroyUtil(void *x);

//void setDate ( Post x ,int d,int m ,int a);

// User getters ------------------------------------------------------------------

//devolve o ID do user
unsigned long getU_id(Util x);

//devolve um pointer do id do user
unsigned long *getU_id_point(Util x);

//devolve o numero de perguntas do user
unsigned int getU_Q(Util x);

//devolve o numero de respostas do user
unsigned int getU_A(Util x);

//devolve o nome do user
unsigned char *getU_name(Util x);
// alloca memoria

//devolve um pointer do nome do user
unsigned char *getU_name_point(Util x);

//devolve a bio de um user
unsigned char *getU_bio(Util x);

//devolve a repetutacao de um user
unsigned int getU_rep(Util x);
// alloca memoria

//Util setters -----------------------------------------------------------------

//incrementa uma unidade nas perguntas do user e devolve o util
Util incU_Q(Util x);

//incrementa uma inidade nas respostas do user e devolve o util
Util incU_A(Util x);

//coloca no user um determinado Id e devolve o util
Util setU_id(Util x, unsigned long num);

//coloca no user um nome e devolve o util
Util setU_name(Util x, const unsigned char *un);

//coloca uma bio no user e devolve o util
Util setU_bio(Util x, const unsigned char *un);

//adiciona na bacia de um user um id e dados e devolve o util
Util add_toBacia(Util x, unsigned int *id, void *dados);

//adiciona no user uma reputacao e devolve o util
Util setU_rep(Util x, unsigned int n);

//Functions --------------------------------------------------------------------

//Util add_toBacia(Util x, unsigned int *id, void *dados);

//devolve um inteiro 1 se for pergunta ou 2 se for resposta e pertencer ha bacia
int belongs_toBacia(Util x, unsigned int Parent_id, char flag);

//percorre a bacia aletrando-a com uma determinada funcao
void* toBacia_transversal(Util x, void (*f)(void *, void *, void *), void *y);

//devolve a posicao de um elemento na bacia
unsigned int *toBacia_lookup(Util x, unsigned int Parent_id);

//devolve o tamanho da bacia
unsigned int toBacia_size( Util x);

//verifica se uma determinada key se econtra num user e devolve um boolean(int)
int toBacia_contains(Util x, unsigned int key);

//coloca no bacia do user um determinado post
Util bind_toBacia(Util x, Post y);

#endif
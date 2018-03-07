#include "date.h"
#ifndef bloco_h
#define bloco_h

#define Max 100

typedef struct utilizador *Util ;
typedef struct post * Post;


// create the Util
/*
->nome
->nº de perguntas 
->nº de respostas
->ID
*/
typedef struct utilizador {

	unsigned int id;
	unsigned char nome[100];
	unsigned int Q;
	unsigned int A;

}*Util ;


// create the Post
/* 
->nome
->ID
->Type
->Fundador
->data
*/
typedef struct post {

	unsigned int id;
	unsigned int type;// 1 Q ; 2 A;
    unsigned int fundador;
	unsigned char nome[100];
	Date data;

}*Post;

void *createPost();
void *createUtil();

void destroyUtil( void* x );
void destroyPost( void* x );

#endif
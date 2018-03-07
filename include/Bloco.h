#include "date.h"
#ifndef bloco_h
#define bloco_h

//#define Max 100

typedef struct utilizador *Util ;
typedef struct post * Post;


// create the Util
/*
->nome
->nº de perguntas 
->nº de respostas
->ID
->BIO
*/
typedef struct utilizador {

	//unsigned long id;
	unsigned char nome[100];
	unsigned int Q;
	unsigned int A;


	unsigned char bio [200];
//	unsigned int AGE;
//	unsigned char loc[100];
//	unsigned int UV;
//	unsigned int DV;

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

	//unsigned int id;
	unsigned char type;// 1 Q ; 2 A;
    unsigned long fundador;
	unsigned char nome[100];
	Date data;

}*Post;

// create a new post
void *createPost();
// create a new util
void *createUtil();

//destroy some specify post
void destroyUtil( void* x );
//destroy a specify post
void destroyPost( void* x );

void setDate ( Post x ,int d,int m ,int a);

#endif
#ifndef bloco_h
#define bloco_h

#define Max 100

typedef struct utilizador *Util ;
typedef struct post * Post;


typedef struct utilizador {

	unsigned char nome[100];
	unsigned int Q;
	unsigned int A;

}*Util ;

typedef struct post {

	unsigned int id;
    unsigned int fundador;
	unsigned char nome[100];

}*Post;

void *createPost();
void *createUtil()

#endif
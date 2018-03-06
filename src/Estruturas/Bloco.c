#include "Bloco.h"


typedef struct utilizador {

	unsigned char nome[100];
	unsigned int perguntas;
	unsigned int respostas;
	unsigned int fundador;

}*Util ;

typedef struct post {

	unsigned int ID;
	unsigned char nome[100];

}*Post;

// create -- destroy -- getters (P e respostas)

// create the Util
void *createUtil(){
	Util x = malloc (sizeof (struct utilizador));
	x->nome = "";
	x->perguntas = "";
	x->respostas = "";
	x->fundador = 0;
	return x;
}

//create a new Post
void *createPost(){
	Post x = malloc (sizeof (struct post));
	x->ID  = 0;
	x->nome = "";
	return x;
}

/*

// Create a Util with some info
void *createUtil_p (char *n , int p , int r , int f ) {
	Util x = malloc (sizeof (struc utilizador));
	x -> nome = n;
	x -> perguntas = p;
	x -> respostas = r;
	x -> fundador = f; 
}

// Create a post with some info
void *createPost_p(int id , char* name){
	Post x = malloc (sizeof (struct post));
	x -> ID = id ; 
	x -> nome = name;
}



// GETTERS!
int getQ(Util x) {
	return ( x->perguntas );
}

int getA(Util x) {
	return ( x->respostas);
}

//SETTERS!

void setQ ( Post x , int q ) {
	x
}

*/



// DESTROY
void destroyPost (Post x){
	Free (x);
}

void destroyUtil (Util x){
	Free (x);
}



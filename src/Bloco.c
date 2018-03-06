#include "Bloco.h"
#include <stdlib.h>
#include <string.h>


void *createPost(){
	Post x = malloc (sizeof (struct post));
	strcpy((char*)x->nome,"Nop");
  	x->id = 0;
	x->type = 0;
	x->fundador = 0;
	return x;
}


// create -- destroy -- getters (P e respostas)

// create the Util
void *createUtil(){
	Util x = malloc (sizeof (struct utilizador));
	strcpy((char*)x->nome,"Nop");
	x->Q = 0;
	x->A = 0;
	x->id = 0;
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






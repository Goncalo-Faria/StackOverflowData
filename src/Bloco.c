#include "Bloco.h"
//#include <stdlib.h>
#include <string.h>

typedef struct utilizador *Util ;
typedef struct post *Post;

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

typedef struct post {

	//unsigned int id;
	unsigned char type;// 1 Q ; 2 A;
    unsigned long fundador;
	unsigned char nome[100];
	unsigned int score;
	GHashTable* bacia;

	//Date data;

}*Post;

void *createPost(){
	Post x = g_malloc (sizeof (struct post));
	strcpy((char*)x->nome,"Nop");
	x->id = 0;
	x->type = 0;
	x->fundador = 0;
	x->score = 0;
	//x->data = g_malloc (sizeof(struct date));
	//x->data = createDate ( 0 , 0 , 0 );
	return x;
}


// create -- destroy -- getters (P e respostas)

void *createUtil(){
	Util x = g_malloc (sizeof (struct utilizador));
	strcpy((char*)x->nome,"Nop");
	strcpy((char*)x->bio, "Nop");
	x->Q = 0;
	x->A = 0;
	x->id = 0;

	x->bacia = g_hash_table_new_full(g_int_hash ,  g_int_equal, NULL , NULL );// key é post.

	
	return x;
}

void destroyUtil( void* x ){
	Util y = (Util) x;

	g_hash_table_destroy(x->bacia);
	g_free(y);
}

/*
void destroyUtil_key( void* x ){
	Util y = (Util) x;
	free(y);
}
*/

void setDate ( Post x ,int d,int m ,int a){
	free_date(x->date);
	x->date = createDate(d,m,a);
}

void destroyPost( void* x ){
	Post y = (Post) x;
	free_date(y->data) ;
	g_free(y);
}

/*
void destroyPost_key( void* x ){
	unsigned int * y = (unsigned int *) x;
	free(y);
}
*/



/*

// Create a Util with some info

void *createUtil_p (char *n , int p , int r , int f ) {
	Util x = g_malloc (sizeof (struc utilizador));
	x -> nome = n;
	x -> perguntas = p;
	x -> respostas = r;
	x -> fundador = f; 
}

// Create a post with some info
void *createPost_p(int id , char* name){
	Post x = g_malloc (sizeof (struct post));
	x -> ID = id ; 
	x -> nome = name;
}

*/

// Util getters

int getQ(Util x) {
	return (x->perguntas);
}

int getA(Util x) {
	return (x->respostas);
}

char* getUN(Util x){
	return (x->nome);
}

char* getB(Util x){
	return (x->bio);
}

// Post getters

long getF(Post x){
	return (x->fundador);
}

char* getN(Post x){
	return (x->nome);
}

int getS(Post x){
	return (x->score);
}

char getT(Post x){
	return (x->type);
}

//Util setters

void setQ(Util x, int q){
	x -> perguntas = q;
}

void setA(Util x, int a){
	x -> respostas = a;
}

void setUN(Util x, char* un){
	strcpy(x->nome, un);
}

void setB(Util x, char* b){
	strcpy(x->bio, b);
}

// Post setters

void setF(Post x, long f){
	x -> fundador = f;
}

void setN(Post x, char* n){
	strncpy(x->nome, n);
}

void setS(Post x, int s){
	x -> score = s;
}

void setT(Post x, char t){
	x -> type = t;
}







#include "Bloco.h"
//#include <stdlib.h>
#include <string.h>
#include <interface.h>


typedef struct utilizador {

	//unsigned long id;
	unsigned char nome[100];
	unsigned int Q;
	unsigned int A;
	unsigned char bio [200];
	GHashTable* bacia;
//	unsigned int AGE;
//	unsigned char loc[100];
//	unsigned int UV;
//	unsigned int DV;

}*Util ;

typedef struct post {

	unsigned int id;
	unsigned char type;// 1 Q ; 2 A;
    unsigned long fundador;
	unsigned char nome[100];
	unsigned int score;

	//Date data;

}*Post;

// Métodos privados.

static void null_check ( void * x ){
	if ( x )
		g_free(x);
}

// Métodos publicos.

void *createPost(){
	Post x = g_malloc (sizeof (struct post));
	strcpy((char*)x->nome,"Nop");
	x->type = 0;
	x->fundador = 0;
	x->score = 0;
	x->id = 0;
	//x->data = g_malloc (sizeof(struct date));
	//x->data = createDate ( 0 , 0 , 0 );
	return x;
}

void destroyPost( void* x ){
	Post y = (Post) x;
	free_date(y->data) ;
	g_free(y);
}

// create -- destroy -- getters (P e respostas)

void *createUtil(){
	Util x = g_malloc (sizeof (struct utilizador));
	strcpy((char*)x->nome,"Nop");
	strcpy((char*)x->bio, "Nop");
	x->Q = 0;
	x->A = 0;

	x->bacia = g_hash_table_new_full(g_int_hash ,  g_int_equal, g_free , null_check );// key é post.

	
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
/*
void setDate ( Post x ,int d,int m ,int a){
	free_date(x->date);
	x->date = createDate(d,m,a);
}
*/

// Util getters

unsigned int getU_Q(Util x) {
	return (x->Q);
}

unsigned int getU_A(Util x) {
	return (x->A);
}

char* getU_name(Util x){
	return (x->nome);
}

char* getU_bio(Util x){
	return (x->bio);
}

// Post getters
unsigned int getP_id(Post x){
	return ( x->id );
}

unsigned long getP_fund(Post x){
	return (x->fundador);
}

char* getP_name(Post x){
	return (x->nome);
}

unsigned int getP_score(Post x){
	return (x->score);
}

unsigned char getP_type(Post x){
	return (x->type);
}

//Util setters

void inc_Q(Util x){
	x ->Q++;
}

void inc_A(Util x){
	x->A++;
}

void setU_name(Util x, char* un){
	strcpy(x->nome, un);
}

void setU_bio(Util x, char* b){
	strcpy(x->bio, b);
}

void add_toBacia(Util x, unsigned int * id , void * dados ){
    
    g_hash_table_insert( x->bacia , (void*) id , dados );
}

int belongs_toBacia ( Util x , unsigned int Parent_id, char flag ){
    
	GHashTable* set = x->bacia;
	// flag == 1; meens Q.
    // flag == 2; meens A.
    if( flag == 1 && g_hash_table_contains ( set , &Parent_id ) )
        // é uma questão e existe.
        return 1;

    if( flag == 2 && g_hash_table_contains ( set , &Parent_id  ) )
        if ( g_hash_table_lookup(set, &Parent_id) )
            //isto significa que existe resposta.
            return 1;

    return 0;


}

// Post setters

void setP_id(Post x, unsigned int o ){
	x->id = o;
}

void setP_fund(Post x, long f){
	x -> fundador = f;
}

void setP_name(Post x, char* n){
	strncpy(x->nome, n);
}

void setP_score(Post x, unsigned int s){
	x -> score = s;
}

void setP_type(Post x, unsigned char t){
	x -> type = t;
}







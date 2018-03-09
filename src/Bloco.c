#include "Bloco.h"
//#include <stdlib.h>
#include <string.h>
#include <interface.h>
#include <glib.h>
//#include "date.h"


typedef struct utilizador {

	//unsigned long id;
	unsigned char *nome;
	unsigned int Q;
	unsigned int A;
	unsigned char *bio;
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
	unsigned char *nome;
	unsigned int score;

	Date moment;

}*Post;

// Métodos privados.

static void null_check ( void * x ){
	if ( x )
		g_free(x);
}

// Métodos publicos.

void *createPost(){
	Post x  = g_malloc (sizeof (struct post));
	x->nome = NULL;
	x->type = 0;
	x->fundador = 0;
	x->score = 0;
	x->id = 0;
	//x->data = g_malloc (sizeof(struct date));
	x->moment = createDate ( 0 , 0 , 0 );
	return x;
}

void destroyPost( void* x ){
	Post y = (Post) x;
	free_date(y->moment);
	null_check(y->nome);
	g_free(y);
}

// create -- destroy -- getters (P e respostas)

void *createUtil(){
	Util x = g_malloc (sizeof (struct utilizador));
	x->nome =NULL;
	x->bio =NULL;
	x->Q = 0;
	x->A = 0;

	x->bacia = g_hash_table_new_full(g_int_hash ,  g_int_equal, g_free , null_check );// key é post.

	
	return x;
}

void destroyUtil( void* x ){
	Util y = (Util) x;

	null_check(y->nome);
	null_check(y->bio);

	g_hash_table_destroy(y->bacia);
	g_free(y);
}

// Util getters

unsigned int getU_Q(Util x) {
	return (x->Q);
}

unsigned int getU_A(Util x) {
	return (x->A);
}

unsigned char* getU_name(Util x){
	// must eliminate
	unsigned char* tmp=NULL;

	if(x->nome ){

		tmp = g_malloc(sizeof(unsigned char)*(strlen((const char*) x->nome ) + 1 )); 
		strcpy((char*)tmp, (const char* )x->nome);
	}
	return tmp ;
}

unsigned char* getU_bio(Util x){
	unsigned char* tmp=NULL;

	if(x->bio){

		tmp = g_malloc(sizeof(unsigned char)*(strlen((const char*) x->bio ) + 1 )); 
		strcpy(( char*)tmp,(const char*) x->bio);
	}
	return tmp ;
}

// Post getters
unsigned int getP_id(Post x){
	return ( x->id );
}

unsigned long getP_fund(Post x){
	return (x->fundador);
}

unsigned char* getP_name(Post x){
	unsigned char* tmp=NULL;

	if(x->nome){

		tmp = g_malloc(sizeof(unsigned char)*(strlen( (const char*)x->nome ) + 1 )); 
		strcpy(( char*)tmp,(const char*) x->nome);
	}
	return tmp ;
}

unsigned int getP_score(Post x){
	return (x->score);
}

unsigned char getP_type(Post x){
	return (x->type);
}

Date getP_date_point( Post x ){
	// memória dinâmica.
	//return createDate( get_day(x->moment), get_month(x->moment), get_year(x->moment) ) ; 
	return x->moment;
}
Date getP_date( Post x ){
	// memória dinâmica.
	return createDate( get_day(x->moment), get_month(x->moment), get_year(x->moment) ) ; 
}
//Util setters

void inc_Q(Util x){
	x->Q++;
}

void inc_A(Util x){
	x->A++;
}

void setU_name(Util x, const unsigned char* un ){
	
	null_check(x->nome);
	x->nome =  g_malloc(sizeof( unsigned char)*(strlen((const char*)un ) + 1 )); 
	strcpy(( char*)x->nome,(const char*) un);
}

void setU_bio(Util x, const unsigned char* un){
	null_check(x->bio);
	x->bio =  g_malloc(sizeof(unsigned char)*(strlen((const char*) un ) + 1 )); 
	strcpy(( char*)x->bio,(const char*) un);
}

void add_toBacia(Util x, unsigned int * id , void * dados ){
    
    g_hash_table_insert( x->bacia , (void*) id , dados );
}

int belongs_toBacia ( Util x , unsigned int Parent_id, char flag ){ // O que acontece na eventualidade de 2 ter uma resposta no post que criou? em datas diferentes.
    
	GHashTable* set = x->bacia;
	// flag == 1; meens Q.
    // flag == 2; meens A.
    if( flag == 1 && g_hash_table_contains ( set , &Parent_id ) )
        // é uma questão e existe.
        return 1;

    if( flag == 2 && g_hash_table_contains ( set , &Parent_id  ) ){
		// é uma Resposta.
        if ( g_hash_table_lookup(set, &Parent_id) )
            //isto significa que existe questão.
            return 1;
		return 2;
		}

    return 0;


}

// Post setters

void setP_id(Post x, unsigned int o ){
	x->id = o;
}

void setP_date( Post x , int d, int m , int a ){
	
	free_date(x->moment);
	x->moment = createDate(d,m,a);
}

void setP_fund(Post x, long f){
	x->fundador = f;
}

void setP_name(Post x, const unsigned char* un){

	null_check(x->nome);
	x->nome = g_malloc(sizeof( unsigned char)*(strlen( (const char*) un ) + 1 )); 
	strcpy(( char*)x->nome, (const char*)un);
}

void setP_score(Post x, unsigned int s){
	x->score = s;
}

void setP_type(Post x, unsigned char t){
	x->type = t;
}







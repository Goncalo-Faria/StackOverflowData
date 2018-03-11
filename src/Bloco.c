#include "Bloco.h"
//#include <stdlib.h>
#include <string.h>
#include <interface.h>
#include <glib.h>
//#include <stdio.h>
//#include "date.h"


typedef struct utilizador {

	unsigned long* id;
	unsigned char *name;
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

	unsigned int * id;
	unsigned char type;// 1 Q ; 2 A;
    unsigned long fundador;
	unsigned char *name;
	unsigned int score;
	unsigned int * parentId;

	Date moment;

}*Post;

// Métodos privados.

static void null_check ( void * x ){
	if ( x )
		g_free(x);
}

// Métodos publicos.

void *createPost(){
	Post x = g_malloc (sizeof (struct post));
	x->name = NULL;
	x->type = 0;
	x->fundador = 0;
	x->score = 0;
	x->id = g_malloc( sizeof(unsigned int ) );
	x->parentId = NULL;
	//x->data = g_malloc (sizeof(struct date));
	x->moment = createDate ( 0 , 0 , 0 );
	return x;
}

void destroyPost( void* x ){
	Post y = (Post) x;
	free_date(y->moment);
	null_check(y->name);
	g_free(y->id);
	null_check(y->parentId);
	g_free(y);
	
}

// create -- destroy -- getters (P e respostas)

void *createUtil(){
	Util x = g_malloc (sizeof (struct utilizador));
	x->name =NULL;
	x->bio =NULL;
	x->id = g_malloc (sizeof (unsigned long ));
	x->Q = 0;
	x->A = 0;

	x->bacia = g_hash_table_new_full(g_int_hash ,  g_int_equal, NULL , NULL );// key é post.

	
	return x;
}

void destroyUtil( void* x ){
	Util y = (Util) x;

	g_free(y->id);

	null_check(y->name);
	null_check(y->bio);

	g_hash_table_destroy(y->bacia);
	g_free(y);
}

// Util getters
unsigned long getU_id( Util x ){

	unsigned long * tmp = x->id;
	return *tmp;
}

unsigned long* getU_id_point( Util x ){
	return x->id;
}

unsigned int getU_Q(Util x) {
	return (x->Q);
}

unsigned int getU_A(Util x) {
	return (x->A);
}

unsigned char* getU_name(Util x){
	// must eliminate
	unsigned char* tmp=NULL;

	if(x->name ){

		tmp = g_malloc(sizeof(unsigned char)*(strlen((const char*) x->name ) + 1 )); 
		strcpy((char*)tmp, (const char* )x->name);
	}
	return tmp ;
}

unsigned char* getU_name_point(Util x){
	return x->name;
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
	unsigned int *y = x->id;
	return ( *y );
}

unsigned int * getP_id_point(Post x){
	return ( x->id );
}

unsigned int getP_parentId(Post x){
	unsigned int *y = x->parentId;
	return ( *y );
}
/*
unsigned int * getP_parentId_point(Post x){
	return ( x->parentId );
}

*/

unsigned long getP_fund(Post x){
	return (x->fundador);
}

unsigned char* getP_name(Post x){
	unsigned char* tmp=NULL;

	if(x->name){

		tmp = g_malloc(sizeof(unsigned char)*(strlen( (const char*)x->name ) + 1 )); 
		strcpy(( char*)tmp,(const char*) x->name);
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

void setU_id( Util x, unsigned long num ){

	unsigned long * tmp = x->id;
	*tmp = num ;
}

void setU_name(Util x, const unsigned char* un ){
	
	null_check(x->name);
	x->name =  g_malloc(sizeof( unsigned char)*(strlen((const char*)un ) + 1 )); 
	strcpy(( char*)x->name,(const char*) un);
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

unsigned int * toBacia_lookup( Util x, unsigned int Parent_id ){
	
	return g_hash_table_lookup(x->bacia, &Parent_id);
}

void bind_toBacia( Util x, Post y ){

    int flag;
    unsigned int tmpid = getP_id(y),tmppr;

    if( y->type == 1 ){ // Questão. y post x user
        //printf("Works bro!\n");
        if ( !Q_belongs_hash(x , tmpid  ) )// verifica se existe!
            add_toBacia(x , y->id , NULL );

    } 
    if( y->type == 2 ){

		//printf("\n YOU HAVE FOUND AN ANSWER \n\n");
		tmppr = getP_parentId( y );
        flag = A_belongs_hash(x ,tmppr );
        if ( ! flag  )// não existe
            add_toBacia(x , y->parentId ,  y->id );
        
        if( flag == 2 ){
			g_hash_table_remove( x->bacia , &tmppr );
			add_toBacia(x , y->parentId ,  y->id  );
        }
        
    }
}
// Post setters

void setP_id(Post x, unsigned int o ){
	unsigned int* y = x->id;
	*y = o;
}

void setP_parentId(Post x, unsigned int o ){
	unsigned int* y;
	
	
	if(!x->parentId){
		x->parentId = g_malloc( sizeof(unsigned int) );
	}
	y = x->parentId;
	*y = o;
}

void setP_date( Post x , int d, int m , int a ){
	
	free_date(x->moment);
	x->moment = createDate(d,m,a);
}

void setP_fund(Post x, long f){
	x->fundador = f;
}

void setP_name(Post x, const unsigned char* un){

	null_check(x->name);
	x->name = g_malloc(sizeof( unsigned char)*(strlen( (const char*) un ) + 1 )); 
	strcpy(( char*)x->name, (const char*)un);
}

void setP_score(Post x, unsigned int s){
	x->score = s;
}

void setP_type(Post x, unsigned char t){
	x->type = t;
}







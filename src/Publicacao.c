#include "Publicacao.h"
#include <string.h>
#include <interface.h>
#include <glib.h>
//#include <stdio.h>
//#include "date.h"

typedef struct post {

	unsigned int * id;
	unsigned char type;// 1 Q ; 2 A;
    unsigned long fundador;
	unsigned char *name;
	unsigned int score;
	unsigned int * parentId;

	Date moment;

}*Post;

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







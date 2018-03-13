#include "Utilizador.h"
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


static void null_check ( void * x ){
	if ( x )
		g_free(x);
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

void toBacia_transversal( Util x, void (*f)(void*, void*, void*) ,void* y){
	
	g_hash_table_foreach( x->bacia , f , y );
	
}

void bind_toBacia( Util x, Post y ){

    int flag;
    unsigned int tmpid = getP_id(y),tmppr;

    if( getP_type(y) == 1 ){ // Questão. y post x user
        //printf("Works bro!\n");
        if ( !Q_belongs_hash(x , tmpid  ) )// verifica se existe!
            add_toBacia(x , getP_id_point(y) , NULL );

    } 
    if( getP_type(y) == 2 ){

		//printf("\n YOU HAVE FOUND AN ANSWER \n\n");
		tmppr = getP_parentId( y );
        flag = A_belongs_hash(x ,tmppr );
        if ( ! flag  )// não existe
            add_toBacia(x , getP_parentId_point(y) ,  getP_id_point(y) );
        
        if( flag == 2 ){
			g_hash_table_remove( x->bacia , &tmppr );
			add_toBacia(x , getP_parentId_point(y) ,  getP_id_point(y) );
        }
        
    }
}
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

	unsigned int *id;
	unsigned char type;// 1 Q ; 2 A;
    unsigned long fundador;
	unsigned char nome[100];
	unsigned int score;

	unsigned int *parentId;
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
	strcpy((char*)x->nome,"Nop");
	x->type = 0;
	x->fundador = 0;
	x->score = 0;
	x->id = g_malloc( sizeof(unsigned int ) );
	x->parentId = NULL;
	//x->data = g_malloc (sizeof(struct date));
	//x->data = createDate ( 0 , 0 , 0 );
	return x;
}

void destroyPost( void* x ){
	Post y = (Post) x;
	free_date(y->moment);
	null_check(y->nome);
	null_check(y->id);
	null_check(y->parentId);
	g_free(y);
	
}

// create -- destroy -- getters (P e respostas)

void *createUtil(){
	Util x = g_malloc (sizeof (struct utilizador));
	strcpy((char*)x->nome,"Nop");
	strcpy((char*)x->bio, "Nop");
	x->Q = 0;
	x->A = 0;

	x->bacia = g_hash_table_new_full(g_int_hash ,  g_int_equal, NULL, NULL);// key é post.

	
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

// Util getters

GHashTable* get_Bacia(Util x){
	return (x->bacia);
}

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

unsigned int * getP_parentId_point(Post x){
	return ( x->parentId );
}

unsigned long getP_fund(Post x){
	return (x->fundador);
}

char* getP_name(Post x){
	return (x->nome);
}

unsigned int getP_Score(Post x){
	return (x->score);
}

unsigned char getP_type(Post x){
	return (x->type);
}

unsigned int getP_answers(Post x){
	return (x->answers);
}

//Util setters

void incQ(Util x){
	x->Q++;
}

void incA(Util x){
	x->A++;
}

void setU_name(Util x, char* un){
	strcpy(x->nome, un);
}

void setU_bio(Util x, char* b){
	strcpy(x->bio, b);
}

unsigned int * toBacia_lookup( Util x, unsigned int Parent_id ){
	
	return g_hash_table_lookup(x->bacia, &Parent_id);
}

void bind_toBacia( Util x, Post y ){

    int flag;
    unsigned int* son, tmpid = getP_id(y), tmppr = getP_parentId( y );

    if( y->type == 1 ){ // Questão. y post x user
        
        if ( !Q_belongs_hash(x , tmpid  ) )// verifica se existe!
            add_toBacia(x , y->id , NULL );

    } 
    if( y->type == 2 ){
        flag = A_belongs_hash(x ,tmppr );
        if ( ! flag  )// não existe
            add_toBacia(x , y->parentId ,  y->id );
        
        if( flag == 2 ){
           son = toBacia_lookup( x ,  tmppr );
           *son = tmpid;
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

void setP_name(Post x, char* n){
	strcpy(x->nome, n);
}

void setP_score(Post x, unsigned int s){
	x->score = s;
}

void setP_type(Post x, unsigned char t){
	x->type = t;
}

void setP_answers(Post x , unsigned int a){
	x->asnwers = a;
}







#ifndef utilizador_h
#define utilizador_h

#include "date.h"
#include "Publicacao.h"

typedef struct utilizador *Util ;


#define Q_belongs_hash(user,id) belongs_toBacia(user,id,1)
#define A_belongs_hash(user,id) belongs_toBacia(user,id,2)

// create a new util
void *createUtil();

//destroy some specify post
void destroyUtil( void* x );

//void setDate ( Post x ,int d,int m ,int a);



// User getters
unsigned long getU_id( Util x );

unsigned long* getU_id_point( Util x );

unsigned int getU_Q(Util x);

unsigned int getU_A(Util x);

unsigned char* getU_name(Util x);
// alloca memoria

unsigned char* getU_name_point(Util x);

unsigned char* getU_bio(Util x);
// alloca memoria


//Util setters

void inc_Q(Util x);

void inc_A(Util x);

void setU_id( Util x, unsigned long num );

void setU_name(Util x, const unsigned char* un );

void setU_bio(Util x, const unsigned char* un);

void add_toBacia(Util x, unsigned int * id , void * dados );



//Functions

void add_toBacia(Util x, unsigned int * id , void * dados );

int belongs_toBacia ( Util x , unsigned int Parent_id, char flag );

void toBacia_transversal( Util x, void (*f)(void*, void*, void*) ,void* y);

unsigned int * toBacia_lookup( Util x, unsigned int Parent_id );

void bind_toBacia( Util x, Post y );










#endif
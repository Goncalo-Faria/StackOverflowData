#ifndef utilizador_h
#define utilizador_h

#include "date.h"
#include "Publicacao.h"

typedef struct utilizador *Util;

#define Q_belongs_hash(user, id) belongs_toBacia(user, id, 1)
#define A_belongs_hash(user, id) belongs_toBacia(user, id, 2)

// create a new util
Util createUtil();

//destroy some specify post
void destroyUtil(void *x);

//void setDate ( Post x ,int d,int m ,int a);

int np_cmp(void *a, void *b, void *user_data);

// User getters
unsigned long getU_id(Util x);

unsigned long *getU_id_point(Util x);

unsigned int getU_Q(Util x);

unsigned int getU_A(Util x);

unsigned char *getU_name(Util x);
// alloca memoria

unsigned char *getU_name_point(Util x);

unsigned char *getU_bio(Util x);
// alloca memoria

//Util setters

Util incU_Q(Util x);

Util incU_A(Util x);

Util setU_id(Util x, unsigned long num);

Util setU_name(Util x, const unsigned char *un);

Util setU_bio(Util x, const unsigned char *un);

Util add_toBacia(Util x, unsigned int *id, void *dados);

//Functions

Util add_toBacia(Util x, unsigned int *id, void *dados);

int belongs_toBacia(Util x, unsigned int Parent_id, char flag);

void* toBacia_transversal(Util x, void (*f)(void *, void *, void *), void *y);

unsigned int *toBacia_lookup(Util x, unsigned int Parent_id);

unsigned int toBacia_size( Util x);

int toBacia_contains(Util x, unsigned int key);

Util bind_toBacia(Util x, Post y);

#endif
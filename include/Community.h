#ifndef community_h
#define community_h

#include "interface.h"
#include "Publicacao.h"
#include "Utilizador.h"

#include "heap.h"

//#include "date.h"

typedef struct TCD_community *TAD_community;
typedef int (*Fcompare)(void *, void *, void *);

TAD_community init(void);
TAD_community clean(TAD_community com);
TAD_community activate(TAD_community com);
TAD_community turnOn_array(TAD_community com, unsigned long n);
TAD_community finalize_array(TAD_community com);
TAD_community assign_tag(TAD_community com, char *key, unsigned int code);
TAD_community userSet_insert_id(TAD_community com, unsigned long *key, Util x);
TAD_community postSet_insert(TAD_community com, unsigned int *key, Post x);
TAD_community insert_array(TAD_community com, Post x);
Util userSet_id_lookup(TAD_community com, unsigned long num);
Post postSet_lookup(TAD_community com, unsigned int num);
unsigned int userSet_size(TAD_community com);
unsigned int postSet_size(TAD_community com);
int is_ON(TAD_community com);
unsigned int code_tag(TAD_community com, char *word);
void *arraySeg_transversal(TAD_community com, Date begin, Date end, void (*functor)(void *, void *), void *user_data);
void *arrayRev_transversal(TAD_community com, int (*functor)(void *, void *), void *user_data);
void *postSet_transversal(TAD_community com, void (*f)(void *, void *, void *), void *x);
void *userSet_id_transversal(TAD_community com, void (*f)(void *, void *, void *), void *x);
HEAP array_Priority_Queue(TAD_community com, unsigned long Qsize, Fcompare q_cmp, int (*filter)(void *, void *), void *user_data);
HEAP arraySeg_Priority_Queue(TAD_community com, Date begin, Date end,unsigned long Qsize,Fcompare q_cmp,int (*filter)(void *, void *), void *user_data);

#endif
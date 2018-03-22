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

// USER HASHTABLE;
TAD_community  userSet_insert_id(TAD_community com, unsigned long *key, Util x);
TAD_community  userSet_insert_name(TAD_community com, unsigned char *key, Util x);
void* userSet_id_transversal(TAD_community com, void (*f)(void *, void *, void *), void *x);
Util userSet_id_lookup(TAD_community com, unsigned long num);
Util userSet_name_lookup(TAD_community com, unsigned char *name);
unsigned int userSet_size(TAD_community com);

// POST HASHTABLE
TAD_community postSet_insert(TAD_community com, unsigned int *key, Post x);
Post postSet_lookup(TAD_community com, unsigned int num);
void* postSet_transversal(TAD_community com, void (*f)(void *, void *, void *), void *x);
unsigned int postSet_size(TAD_community com);

// POST BALANCED TREE;

TAD_community turnOn_array(TAD_community com, unsigned long n);
TAD_community  insert_array(TAD_community com, Post x);
TAD_community  finalize_array(TAD_community com);

void* arraySeg_transversal(TAD_community com, Date begin, Date end,
                          void (*functor)(void *, void *),
                          void *user_data);

HEAP array_Priority_Queue(TAD_community com,
                          unsigned long Qsize,
                          Fcompare q_cmp,
                          int (*filter)(void *, void *),
                          void *user_data);

HEAP arraySeg_Priority_Queue(TAD_community com, Date begin, Date end,
                             unsigned long Qsize,
                             Fcompare q_cmp,
                             int (*filter)(void *, void *),
                             void *user_data);

int date_compare(const void *a /*x*/, const void *b /*y*/, void *user_data);
int reverseCompare(void *a, void *b, void *fun);

#endif
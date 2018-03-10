#ifndef community_h
#define community_h

#include "interface.h"
#include "Bloco.h"
//#include "date.h"

//typedef struct TCD_community * TAD_community;

TAD_community init(void);
TAD_community clean(TAD_community com);




// USER HASHTABLE;
int userSet_insert(TAD_community com, unsigned long * key, Util x );
void userSet_transversal( TAD_community com, void (*f)(void*, void*, void*) ,void* x );
Util userSet_lookup( TAD_community com, unsigned long num );
unsigned int userSet_size(TAD_community com);

// POST HASHTABLE
int postSet_insert(TAD_community com, unsigned int * key, Post x );
Post postSet_lookup( TAD_community com, unsigned int num );
void postSet_transversal( TAD_community com, void (*f)(void*, void*, void*) ,void* x );
unsigned int postSet_size(TAD_community com);
// POST BALANCED TREE;
// estás funções terão de ser substituidas assim que a AVL esteja terminada.
void postTree_insert(TAD_community com, Date key, Post x);
void postTree_transversal( TAD_community com, int (*f)(void*, void*, void*) ,void* x);




int date_compare ( const void* a /*x*/, const void* b /*y*/,void* user_data);

#endif
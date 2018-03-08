#ifndef community_h
#define community_h

#include "Bloco.h"

typedef struct TCD_community * TAD_community;

TAD_community init(void);

TAD_community clean(TAD_community com);


unsigned int userSet_size(TAD_community com);
unsigned int postSet_size(TAD_community com);
Util userSet_lookup( TAD_community com, unsigned long num );
Post postSet_lookup( TAD_community com, unsigned int num );

void userSet_transversal( TAD_community com, void (*f)(void*, void*, void*) ,void* x );
void postSet_transversal( TAD_community com, void (*f)(void*, void*, void*) ,void* x );
void postTree_transversal( TAD_community com, void (*f)(void*, void*, void*) ,void* x);


#endif
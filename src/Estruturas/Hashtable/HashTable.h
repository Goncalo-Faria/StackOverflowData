#ifndef LINKEDHASH_h
#define LINKEDHASH_h

typedef struct *Htable;


#include <stdlib.h>

/**
 * 
 * Construtores.
 * 
 */

Htable create_Ht (float loadMax, float loadMin );
void destroy_Ht ( Htable tb );
//


// métodos.

int add_Ht(Htable tb ,unsigned char * key ,void * info, size_t spc,int*collision );
void * search_Ht ( Htable tb, unsigned  char* key, size_t * spc );
int remove_Ht(Htable tb,unsigned char*key);

#endif
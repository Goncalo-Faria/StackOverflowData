#ifndef LINKEDHASH_h
#define LINKEDHASH_h

typedef struct htable *Htable;


/**
 * 
 * Construtores.
 * 
 */

Htable create_Ht (float loadMax, float loadMin );
void destroy_Ht ( Htable tb , int flag );
//


// métodos.

int add_Ht(Htable tb ,unsigned char * key ,void * info, unsigned long spc,int*collision );
void * search_Ht ( Htable tb, unsigned  char* key, unsigned long * spc );
int remove_Ht(Htable tb,unsigned char*key);

#endif
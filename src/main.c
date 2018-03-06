#include <date.h>
#include <glib.h>
#include <stdio.h>
#include "interface.h"



int main(){
  /*
  Date d = createDate(1,2,2017);
  printf("Dia: %i\n", get_day(d));
  return 0;
  */
  
  TAD_community x = init();

  x = load( x , "practicedata" );

  printf("USER::%d \n",g_hash_table_size(x->post));

  clean(x);
  return 1;


    
    /*
    GHashTable* hash = g_hash_table_new(g_int_hash,  g_int_equal);
    int num1 = 4242, num2 =21212;
    g_hash_table_insert(hash,(void*)&num1,"Cheese");// hash -> chava -> info;
    g_hash_table_insert(hash,(void*)&num2,"Treats");// hash -> chave -> info

    printf("There are %d keys in the hash table\n",
        g_hash_table_size(hash));

    printf("%d\n", sizeof(unsigned int) );

    printf("Jazzy likes %s\n",g_hash_table_lookup(hash,&num1));

    g_hash_table_destroy(hash);

    return 0;
    */

} 

/**
 *
 * 
 * 
 * 
 *  
  */
#include <date.h>
#include <stdio.h>
#include "interface.h"
#include "Community.h"




int main(void){
  /*
  Date d = createDate(1,2,2017);
  printf("Dia: %i\n", get_day(d));
  return 0;
  */
    STR_pair q1;
    LONG_list q2;
    int i,n;

    TAD_community com = init();

    load( com , "android" );
    
    printf("______________________\n");
    printf("|->Q1\n\n");
    q1 = info_from_post(com, 97086 );

    printf("Publication name :: %s\n",get_fst_str(q1) );
    printf("Publicant name :: %s\n",get_snd_str(q1));
    free_str_pair(q1);
    
    n=20;
    printf("______________________\n");
    printf("|->Q2\n\n");
    q2 = top_most_active(com, n);
    for (i=0; i< n; i++)
        printf(">> %d <<\n",(int)get_list(q2, i) );  
    printf("______________________\n");

    clean(com);

    return 1;
}

    
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



/**
 *
 * 
 * 
 * 
 *  
  */
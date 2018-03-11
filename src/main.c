#include <date.h>
#include <stdio.h>
#include "interface.h"
#include <glib.h>
#include "Community.h"




int main(void){
  /*
  Date d = createDate(1,2,2017);
  printf("Dia: %i\n", get_day(d));
  return 0;
  */
    USER q5;
    STR_pair q1;
    LONG_pair q3;
    LONG_list q2;
    long *l;
    LONG_list q6;
    Date begin=createDate(16, 1, 2011) , end = createDate( 3 , 3 , 2013);
    int i,n;

    TAD_community com = init();

    load( com , "android" );

    printf("______________________\n");
    printf("|->Q1\n\n");
    q1 = info_from_post(com, 97086 );

    printf("Publication name :: %s\n",get_fst_str(q1) );
    printf("Publicant name :: %s\n",get_snd_str(q1));
    free_str_pair(q1);
    
    printf("______________________\n");
    printf("|->Q2\n\n");
    n=20;
    q2 = top_most_active(com, n);
    for (i=0; i< n; i++)
        printf(">> %d <<\n",(int)get_list(q2, i) );  
    free_list(q2);


    printf("______________________\n");
    printf("|->Q3\n\n");
    q3 = total_posts(com, begin, end);
    
    printf("from :: 16 - 01 - 2011\n");
    printf("to   :: 03 - 03 - 2013\n");

    printf("Number of Questions :: %ld \n", get_fst_long(q3) );
    printf("Number of Questions :: %ld \n", get_snd_long(q3) );
    free_long_pair(q3);

    
    printf("______________________\n");
    printf("|->Q5\n\n");
    q5 = get_user_info(com, 9897);


    printf("Short user bio :: \n%s \n",  get_bio(q5) );

    printf("Last 10 posts :: \n");

    l = get_10_latest_posts(q5);
    for(i=0; i<10; i++ ){
       printf(" POST %d :: %ld  \n", i+1,l[i] );
    }
    g_free(l);
    free_user(q5);

    printf("______________________\n");
    printf("|->Q6\n\n");

    n=20;
    q6 = most_voted_answers(com, n , begin, end);


    for (i=0; i< n; i++)
        printf(">> %d <<\n",(int)get_list(q6, i) );
        

    g_free(q6);



    clean(com);

    return 1;
}




/**
 *
 * 
 * 
 * 
 *  
  */
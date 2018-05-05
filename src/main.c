#include <date.h>
#include <stdio.h>
#include "interface.h"
#include <glib.h>
#include "Community.h"
#include "stdlib.h"

//tmp
#include "bArray.h"
#include "heap.h"
#include <time.h>
#include "comondec.h"
#include "limits.h"




int main(int argc, char *argv[])
{
    clock_t t1, t2;
    USER q5;
    Util usq2;
    Post q6p, q7p, q9p, q8p;
    STR_pair q1;
    LONG_pair q3;
    char *tmp;
    long *l;
    LONG_list q9, q2, q6, q7, q8, q11, q4;
    long q10;
    Date begin , end ; //= createDate(31, 7, 2016);
    int n,i;
    //int *bg, *ed;
    Date pdate;
    TAD_community com;
    double time_spent = 0;
    //double sum;
    //10.084375
    //10.430469
    if (argc < 2)
    {
        printf("--------------------------------------------------------\n");
        printf("\tIndica o path quando invocas o programa\n");
        printf("--------------------------------------------------------\n");
        exit(-1);
    }

    t1 = clock();
    com = init();
    com = load(com, argv[1]);
    

// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 2 ------------------------------------------------------------------------------------------------------------------------------

    
    n = 100;
    time_spent =0;
    //Nao esquecer , quando for para testar tirar os printf
    for (i = 0 ; i < 1000 ; i++ ){
        t1 = clock();
        q2 = top_most_active(com, 10);
        if (q2){
                      
            
        free_list(q2);
        }
        t2 = clock();
        time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;
    }
     printf ("Tempo demorado :%lG\n" , time_spent/1000);
 

/* -----------------------------------------------------------------------------------------------------------------------------------------
// Question 3 ------------------------------------------------------------------------------------------------------------------------------
 
    time_spent = 0;

    begin = createDate(1,1,2014);
    end = createDate(31,12,2014);

    for (i = 0 ; i < 1000 ; i++ ){
    t1 = clock();
    q3 = total_posts(com, begin, end);

    if(q3)
    free_long_pair(q3);

    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC; 
    }
   
    printf ("Tempo demorado :%lG\n" , time_spent/1000);
 }

// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 4 ------------------------------------------------------------------------------------------------------------------------------

    time_spent = 0;
    
   
    begin = createDate(1,1,2014);
    end = createDate(31,1,2014);

    for (i=0 ; i< 1000 ; i++){
	t1 = clock();    
	    q4 = questions_with_tag(com, "nautilus", begin, end);
        if(q4)
        free_list(q4);  
        
 	t2 = clock();
        time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;

    }

    printf ("Tempo demorado :%lG\n" , time_spent/1000);
}
// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 5 ------------------------------------------------------------------------------------------------------------------------------

    
    time_spent =0;
    for (int i=0; i<1000; i++){
        t1 = clock();
        q5 = get_user_info(com, 449);
            if (q5)
    		free_user(q5);
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC; 
    }
     printf ("Tempo demorado :%lG\n" , time_spent/1000);
 }

// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 6 ------------------------------------------------------------------------------------------------------------------------------


    begin = createDate(1,5,2013);
    end = createDate(6,5,2013);
    time_spent =0;
    n = 50;
    for (int i = 0; i < 1000 ; i++){
        t1 = clock();
        q6 = most_voted_answers(com, n, begin, end);
        if (q6)
    g_free(q6);
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;     
    }
     printf ("Tempo demorado :%lG\n" , time_spent/1000);
 }
 
    

// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 7 ------------------------------------------------------------------------------------------------------------------------------
  
    n = 100;
    time_spent =0;
    begin = createDate(1,1,2012);
    end = createDate(31,12,2012);
    for (int i = 0; i < 1000 ; i++){
        t1 = clock();
        q7 = most_answered_questions(com, n, begin, end);
        if (q7)
    g_free(q7);
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;     
    }
         printf ("Tempo demorado :%lG\n" , time_spent/1000);
 }

// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 8 ------------------------------------------------------------------------------------------------------------------------------

    n = 10;
    time_spent =0;
  
    //Parâmetro 2: palavra='glib', N=10
    for (int i = 0; i < 1000 ; i++){
        t1 =clock();
        q8 = contains_word(com, "glib", n);
        if (q8)
   	 g_free(q8);
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC; 
    }
     printf ("Tempo demorado :%lG\n" , time_spent/1000);
 }
 
    

// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 9 ------------------------------------------------------------------------------------------------------------------------------

   
    n = 5;
    time_spent =0;
    for (int i = 0; i < 1000 ; i++){
        q9 = both_participated(com, 253,455, n);
        if (q9)
    g_free(q9);
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC; 
    }
     printf ("Tempo demorado :%lG\n" , time_spent/1000);
 }

// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 10 ------------------------------------------------------------------------------------------------------------------------------

   
   time_spent =0;
    for (int i = 0; i < 1000 ; i++){
        t1 = clock();
        q10 = better_answer(com, 5942);
            if (q10)
               
    g_free(q10);
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;  
    }
     printf ("Tempo demorado :%lG\n" , time_spent/1000);
 }

// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 11 ------------------------------------------------------------------------------------------------------------------------------

    

    n = 10;
    begin = createDate(1,11,2014);
    end = createDate(31,12,2014);
    time_spent =0;
    for (int i = 0; i < 1000 ; i++){
        t1 = clock();
        q11 = most_used_best_rep(com, n, begin, end);
            if (q11)
                g_free(q11);
                
            
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;   
    }
     printf ("Tempo demorado :%lG\n" , time_spent/1000);
 
//
*/
    clean(com);
    return 1;

}



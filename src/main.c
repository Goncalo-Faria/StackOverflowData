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
// Question 1 ------------------------------------------------------------------------------------------------------------------------------

/*
    
    //q1 = info_from_post(com, 801049);
    time_spent =0;
    //Nao esquecer , quando for para testar tirar os printf
    for (i = 0 ; i < 1000 ; i++ ){
        t1 = clock();
        q1 = info_from_post(com,796430);
        if (q1)
        {
            tmp = get_fst_str(q1);
            //printf("Publication name :: \t %s\n", tmp);
            if (tmp)
                g_free(tmp);
                
            tmp = get_snd_str(q1);

            //printf("Publicant name :: \t %s\n", get_snd_str(q1));
            if(tmp)
                g_free(tmp);
                
            free_str_pair(q1);
        }
        //else {
        //    printf(" Nao existe colega! \n");
      //  }
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;
    }
    printf ("Tempo demorado :%f" , time_spent/1000);
} */

// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 2 ------------------------------------------------------------------------------------------------------------------------------
/*  
    
    n = 100;
    time_spent =0;
    //Nao esquecer , quando for para testar tirar os printf
    for (i = 0 ; i < 1000 ; i++ ){
        t1 = clock();
        //q2 = top_most_active(com,1000);
        q2 = top_most_active(com, 10);
        if (q2){
            for (i = 0; i < n; i++){
                //printf("| %d >> %d ", i + 1, (int)get_list(q2, i));
                usq2 = userSet_id_lookup(com, get_list(q2, i));
                //printf(" \t %d \n", getU_A(usq2) + getU_Q(usq2));
            }
        free_list(q2);
        }
        t2 = clock();
        time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;
    }
     printf ("Tempo demorado :%f" , time_spent/1000);
 }
*/
// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 3 ------------------------------------------------------------------------------------------------------------------------------
/* 
    time_spent = 0;

    begin = createDate(1,1,2014);
    end = createDate(31,12,2014);

    for (i = 0 ; i < 1000 ; i++ ){
    t1 = clock();
    q3 = total_posts(com, begin, end);


    
    //printf("Number of Questions ::\t %ld \n", get_fst_long(q3));
    //printf("Number of Answers   ::\t %ld \n", get_snd_long(q3));
    if(q3)
    free_long_pair(q3);

    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC; 
    }
   
    printf ("Tempo demorado :%f" , time_spent/1000);
 }
*/
// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 4 ------------------------------------------------------------------------------------------------------------------------------
/*
    time_spent = 0;
    t1 = clock();
   
    begin = createDate(1,1,2014);
    end = createDate(31,1,2014);

    for (i=0 ; i< 1000 ; i++){
        q4 = questions_with_tag(com, "nautilus", begin, end);
        if(q4){


        for (i = 0; i < get_size_list(q4); i++){

            q6p = postSet_lookup(com, get_list(q4, i));
            pdate = getP_date(q6p);
            printf(" %d- %d- %d \n", get_day(pdate), get_month(pdate), get_year(pdate));
        }

        t2 = clock();
        time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;
        free_list(q4);  
        }
    }

    printf ("Tempo demorado :%f" , time_spent/1000);
}*/
// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 5 ------------------------------------------------------------------------------------------------------------------------------
/*
    
    time_spent =0;
    for (int i=0; i<1000; i++){
        t1 = clock();
        q5 = get_user_info(com, 449);
            if (q5){
                tmp = get_bio(q5);
                printf("Short user bio :: \n%s \n", tmp);
                printf("Last 10 posts  :: \n");

                l = get_10_latest_posts(q5);

                for (i = 0; i < 10; i++){
                    if (l[i]) {
                        printf(" POST %d :: %ld   ", i + 1, l[i]);
                        q6p = postSet_lookup(com, l[i]);

                        pdate = getP_date_point(q6p);
                        printf(" - %d - %d - %d - \n", get_day(pdate), get_month(pdate), get_year(pdate));
                    }
                }
            }
    free_user(q5);
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC; 
    }
     printf ("Tempo demorado :%f" , time_spent/1000);
 }
*/
// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 6 ------------------------------------------------------------------------------------------------------------------------------

/* 
    begin = createDate(1,5,2013);
    end = createDate(6,5,2013);
    time_spent =0;
    n = 50;
    for (int i = 0; i < 1000 ; i++){
        t1 = clock();
        q6 = most_voted_answers(com, n, begin, end);
        if (q6){
            for (i = 0; i < n; i++){

                if ((unsigned int)get_list(q6, i)){
                    q6p = postSet_lookup(com, (unsigned int)get_list(q6, i));
                }
             
        }
    }
    g_free(q6);
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;     
    }
     printf ("Tempo demorado :%f" , time_spent/1000);
 }
 */
    

// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 7 ------------------------------------------------------------------------------------------------------------------------------
/*  
    n = 100;
    time_spent =0;
    begin = createDate(1,1,2012);
    end = createDate(31,12,2012);
    for (int i = 0; i < 1000 ; i++){
        t1 = clock();
        q7 = most_answered_questions(com, n, begin, end);
        if (q7){
            for (i = 0; i < n; i++){

                if ((unsigned int)get_list(q7, i)){
                    printf(">> %d   ", (int)get_list(q7, i));
                    q7p = postSet_lookup(com, (unsigned int)get_list(q7, i));
                    printf("\t < %d > \n", getP_ansCount(q7p));
                }
            else
                printf(" Can't find that post bro\n");
            }
        } 
    g_free(q7);
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;     
    }
         printf ("Tempo demorado :%f" , time_spent/1000);
 }
*/
// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 8 ------------------------------------------------------------------------------------------------------------------------------
/*
    n = 10;
    time_spent =0;
  
    //Parâmetro 2: palavra='glib', N=10
    for (int i = 0; i < 1000 ; i++){
        t1 =clock();
        q8 = contains_word(com, "glib", n);
        if (q8){
            for (i = 0; i < n; i++) {
                if ((unsigned int)get_list(q8, i)){
                    q8p = postSet_lookup(com, (unsigned int)get_list(q8, i));
                    pdate = getP_date_point(q8p);
            }
        }
    }
    g_free(q8);
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC; 
    }
     printf ("Tempo demorado :%f" , time_spent/1000);
 }
 */
    

// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 9 ------------------------------------------------------------------------------------------------------------------------------

   /*
    n = 5;
    time_spent =0;
    for (int i = 0; i < 1000 ; i++){
        q9 = both_participated(com, 253,455, n);
        if (q9){
            for (i = 0; i < n; i++){
             if ((unsigned int)get_list(q9, i)){
                q9p = postSet_lookup(com, (unsigned int)get_list(q9, i));
                pdate = getP_date_point(q9p);  
            }
        }
    }
    g_free(q9);
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC; 
    }
     printf ("Tempo demorado :%f" , time_spent/1000);
 }
*/
// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 10 ------------------------------------------------------------------------------------------------------------------------------

   /*
   time_spent =0;
    for (int i = 0; i < 1000 ; i++){
        t1 = clock();
        q10 = better_answer(com, 5942);
            if (q10){
                q9p = postSet_lookup(com, (unsigned long)q10);
            }

    g_free(q10);
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;  
    }
     printf ("Tempo demorado :%f" , time_spent/1000);
 }
*/
// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 11 ------------------------------------------------------------------------------------------------------------------------------

    /*

    n = 10;
    begin = createDate(1,11,2014);
    end = createDate(31,12,2014);
    time_spent =0;
    for (int i = 0; i < 1000 ; i++){
        t1 = clock();
        q11 = most_used_best_rep(com, n, begin, end);
            if (q11){
                for (i = 0; i < n; i++){
                    if (get_list(q11, i)){
                        printf(">> %d  || %ld \n", (int)i + 1, get_list(q11, i));
                    }
                g_free(q11);
                }
            }
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;   
    }
     printf ("Tempo demorado :%f" , time_spent/1000);
 


    g_free(begin);
    g_free(end);
    clean(com);
    return 1;

}
*/


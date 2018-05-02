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

    printf("|->Q1\n\n");
    //q1 = info_from_post(com, 801049);
    time_spent =0;
    //Nao esquecer , quando for para testar tirar os printf
    for (i = 0 ; i < 1000 ; i++ ){
        t1 = clock();
        q1 = info_from_post(com,796430);
        if (q1)
        {
            tmp = get_fst_str(q1);
            printf("Publication name :: \t %s\n", tmp);
            g_free(tmp);
            tmp = get_snd_str(q1);

            printf("Publicant name :: \t %s\n", get_snd_str(q1));
            g_free(tmp);
            free_str_pair(q1);
        }
        else {
            printf(" Nao existe colega! \n");
        }
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;
    }
    printf ("Tempo demorado :%f" , time_spent/1000);
} 
*/
// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 2 ------------------------------------------------------------------------------------------------------------------------------
 /*   
    printf("|->Q2\n\n");
    n = 30;
    time_spent =0;
    //Nao esquecer , quando for para testar tirar os printf
    for (i = 0 ; i < 1000 ; i++ ){
        t1 = clock();
        //q2 = top_most_active(com,1000);
        q2 = top_most_active(com, 10);
        if (q2){
            for (i = 0; i < n; i++){
                printf("| %d >> %d ", i + 1, (int)get_list(q2, i));
                usq2 = userSet_id_lookup(com, get_list(q2, i));
                printf(" \t %d \n", getU_A(usq2) + getU_Q(usq2));
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
    printf("|->Q3\n\n");
   
    time_spent = 0;
    // Parâmetro 1: begin=2016-07-01, end=2016-07-31
    // Parâmetro 2: begin=2014-01-01, end=2014-12-31

    begin = createDate(1,7,2016);
    end = createDate(31,7,2016);

    for (i = 0 ; i < 1000 ; i++ ){
    t1 = clock();
    q3 = total_posts(com, begin, end);

    printf("from :: 2016-07-01\n");
    printf("to   :: 2016-07-31\n");

    //2 parametro -> begin=2014-01-01, end=2014-12-31
    
    printf("Number of Questions ::\t %ld \n", get_fst_long(q3));
    printf("Number of Answers   ::\t %ld \n", get_snd_long(q3));
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
    printf("|->Q4\n\n");
    time_spent = 0;
    t1 = clock();
    //parametro 1 -> begin=2013-03-01, end=2013-03-31 | package-management
    //parametro 2 -> begin=2014-01-01, end=2014-01-31, tag='nautilus'
    begin = createDate(1,3,2013);
    end = createDate(31,3,2013);

    for (i=0 ; i< 1000 ; i++){
        q4 = questions_with_tag(com, "package-management", begin, end);

        printf(" %d \n", get_size_list(q4));

        for (i = 0; i < get_size_list(q4); i++){

            q6p = postSet_lookup(com, get_list(q4, i));
            pdate = getP_date(q6p);
            printf(" %d- %d- %d \n", get_day(pdate), get_month(pdate), get_year(pdate));
        }
    }

    printf ("Tempo demorado :%f" , time_spent/1000);
}*/
// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 5 ------------------------------------------------------------------------------------------------------------------------------
/*
    printf("|->Q5\n\n");
    //parametro 1 -> id=15811
    //paraetro 2 -> id=449
    time_spent =0;
    for (int i=0; i<1000; i++){
        t1 = clock();
        q5 = get_user_info(com, 15811);
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
                else
                    printf(" Can't find that post bro\n");
                }
        //g_free(tmp);
        //g_free(l);
        free_user(q5);
    }
    else{
        printf(" Nao existe colega! \n");
    }
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC; 
    }
     printf ("Tempo demorado :%f" , time_spent/1000);
 }
*/
// -----------------------------------------------------------------------------------------------------------------------------------------
// Question 6 ------------------------------------------------------------------------------------------------------------------------------
/*
    printf("|->Q6\n\n");
    
    //Parâmetro 1 -> begin=2015-11-01, end=2015-11-30, N=5
    //Parâmetro 2 -> begin=2013-05-01, end=2013-05-06, N=50
    begin = createDate(1,11,2015);
    end = createDate(30,11,2015);
    time_spent =0;
    n = 5;
    for (int i = 0; i < 1000 ; i++){
        t1 = clock();
        q6 = most_voted_answers(com, n, begin, end);
        if (q6){
            for (i = 0; i < n; i++){

                if ((unsigned int)get_list(q6, i)){
                    printf(">> %d   ", (int)get_list(q6, i));
                    q6p = postSet_lookup(com, (unsigned int)get_list(q6, i));
                    printf("\t < %d > \n", getP_votes(q6p));
                }
                else
                printf(" Can't find that post bro\n");
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
    printf("|->Q7\n\n");
    n = 10;
    time_spent =0;
    //Parâmetro 1: begin=2014-08-01, end=2014-08-11, N=10
    //Parâmetro 2: begin=2012-01-01, end=2012-12-31, N=100
    begin = createDate(1,8,2014);
    end = createDate(11,8,2014);
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
    printf("|->Q8\n\n");
    //Nao esquecer , quando for para testar tirar os printf
    n = 10;
    time_spent =0;
    //Parâmetro 1: palavra='kde', N=10
    //Parâmetro 2: palavra='glib', N=10
    for (int i = 0; i < 1000 ; i++){
        t1 =clock();
        q8 = contains_word(com, "kde", n);
        if (q8){
            for (i = 0; i < n; i++) {
                if ((unsigned int)get_list(q8, i)){
                    q8p = postSet_lookup(com, (unsigned int)get_list(q8, i));
                    pdate = getP_date_point(q8p);
                if (q8p)
                    printf(" %d ||  %d-%d-%d || \t name : : %s || \n", i + 1, get_day(pdate), get_month(pdate), get_year(pdate), getP_name_point(q8p));
                }
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
    printf("|->Q9\n\n");
    n = 10;
    //Parâmetro 1: use1=87, user2=5691, N=10
    //Parâmetro 2: use1=253, user2=455, N=5
    time_spent =0;
    for (int i = 0; i < 1000 ; i++){
        q9 = both_participated(com, 87,5691, n);
        if (q9){
            for (i = 0; i < n; i++){

             if ((unsigned int)get_list(q9, i)){
                printf(">> %d   ", (int)get_list(q9, i));
                q9p = postSet_lookup(com, (unsigned int)get_list(q9, i));

                pdate = getP_date_point(q9p);
                printf("\t - %d - %d - %d - \n", get_day(pdate), get_month(pdate), get_year(pdate));
            }
            else
                printf(" Can't find that post bro\n");
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
    printf("|->Q10\n\n");
    //Parâmetro 1: id=30334
    //Parâmetro 2: id=5942
    //time_spent =0;
    for (int i = 0; i < 1000 ; i++){
        t1 = clock();
        q10 = better_answer(com, 35580);
            if (q10){
                printf("----1>| %ld |<1----\n", q10);
                //g_free(q10);
                q9p = postSet_lookup(com, (unsigned long)q10);

                printf(" ----1>| votes _%d ! comment _%d ! score _%d ! \n", (int)getP_votes(q9p), (int)getP_nComment(q9p), (int)getP_score(q9p));
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
 //Parâmetro 1: begin=2013-11-01, end=2013-11-30, N=5
 //Parâmetro 2: begin=2014-01-01, end=2014-12-31, N=10
    printf("|->Q11\n\n");
    n = 10;
    begin = createDate(1,11,2013);
    end = createDate(30,11,2013);
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


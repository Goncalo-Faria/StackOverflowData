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

static int print(void *a, void *garb)
{
    int *x = (int *)a;
    printf("->%d ||| \n", *x);
    return 1;
}

int main(void)
{
    clock_t t1, t2;
    USER q5;
    Util usq2;
    Post q6p;
    STR_pair q1;
    LONG_pair q3;
    LONG_list q2;
    long *l;
    LONG_list q6;
    Date begin = createDate(16, 1, 2011), end = createDate(3, 3, 2013);
    //int i, *the_test_tmp;
    int n;
    //int *bg, *ed;
    Date pdate;

    //bArray the_test;
    //int **envoy;
    //HEAP the_fst_beap,Pq;
    TAD_community com;
    int i;
    double time_spent = 0;
    //double sum;
    //10.084375
    //10.430469

    t1 = clock();
    com = init();
    com = load(com, "askubuntu");

    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;

    printf("\n.. Loading Terminaterd .. \nload -> time. :: %f \n", (float)(time_spent));

    printf("______________________\n");
    printf("|->Q1\n\n");
    q1 = info_from_post(com, 97086);
    if (q1)
    {
        printf("Publication name :: %s\n", get_fst_str(q1));
        printf("Publicant name :: %s\n", get_snd_str(q1));
        free_str_pair(q1);
    }
    else
        printf(" Nao existe colega! \n");

    printf("______________________\n");
    printf("|->Q2\n\n");
    n = 40;
    q2 = top_most_active(com, n);
    for (i = 0; i < n; i++)
    {
        printf(">> %d <<", (int)get_list(q2, i));
        usq2 = userSet_id_lookup(com, get_list(q2, i));
        printf(" \t %d \n", getU_A(usq2) + getU_Q(usq2));
    }
    free_list(q2);

    printf("______________________\n");
    printf("|->Q3\n\n");

    q3 = total_posts(com, begin, end);

    printf("from :: 16 - 01 - 2011\n");
    printf("to   :: 03 - 03 - 2013\n");

    printf("Number of Questions :: %ld \n", get_fst_long(q3));
    printf("Number of Answers :: %ld \n", get_snd_long(q3));
    free_long_pair(q3);

    printf("______________________\n");
    printf("|->Q5\n\n");
    q5 = get_user_info(com, 9897);
    if (q5)
    {
        printf("Short user bio :: \n%s \n", get_bio(q5));
        printf("Last 10 posts :: \n");

        l = get_10_latest_posts(q5);

        for (i = 0; i < 10; i++)
        {

            printf(" POST %d :: %ld   ", i + 1, l[i]);
            q6p = postSet_lookup(com, l[i]);
            pdate = getP_date_point(q6p);
            printf(" - %d - %d - %d - \n", get_day(pdate), get_month(pdate), get_year(pdate));
        }
        g_free(l);
        free_user(q5);
    }
    else printf(" Nao existe colega! \n");

    printf("______________________\n");
    printf("|->Q6\n\n");

    n = 50;
    q6 = most_voted_answers(com, n, begin, end);

    for (i = 0; i < n; i++)
    {
        printf(">> %d <<  ", (int)get_list(q6, i));
        if ((unsigned int)get_list(q6, i))
        {
            q6p = postSet_lookup(com, (unsigned int)get_list(q6, i));
            printf(" < %d > \n", getP_score(q6p));
        }
    }

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
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

int main(int argc, char *argv[])
{
    clock_t t1, t2;
    double time_spent = 0;
    int i, n, j, *l;
    TAD_community com;
    HEAP hp;
    Date begin = createDate(16, 1, 2010), end = createDate(20, 9, 2017);
    if (argc < 2)
    {
        printf("--------------------------------------------------------\n");
        printf("\tIndica o path quando invocas o programa\n");
        printf("--------------------------------------------------------\n");
        exit(-1);
    }
    n = 1;
    //time(NULL);

    for (i = 0; i < 1; i++)
    {
        
        com = init();
        com = load(com, argv[1]);
        n=1000;

        for (j = 0; j < n; j++)
        {
            t1 = clock();
            most_used_best_rep(com, 100000 , begin, end);
            /*
            hp = create_H(free, int_cmp, NULL);

            for (i = 0; i < 400000; i++)
            {
                l = malloc(sizeof(int));
                *l = rand();
                hp = add_Heap(hp, l);
            }

            for (i = 0; i < 400000; i++)
            {
                l = rem_Heap(hp);
            }
            destroy_H(hp);
            */
            t2 = clock();
            time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;
        }

        //clean(com);
    }
    printf("time: %f \n", (float)time_spent / n);
    return (1);
}

/*
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
    Date begin = createDate(16, 1, 2013), end = createDate(3, 3, 2015);
    int n;
    //int *bg, *ed;
    Date pdate;
    TAD_community com;
    int i;
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

    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;

    printf("\n.. Loading Terminaterd .. \nload -> time. :: %f \n", (float)(time_spent));

    printf("______________________\n");
    printf("|->Q1\n\n");
    q1 = info_from_post(com, 30334);
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
    else
        printf(" Nao existe colega! \n");

    printf("______________________\n");
    printf("|->Q2\n\n");
    n = 30;
    q2 = top_most_active(com, n);
    if (q2)
    {
        for (i = 0; i < n; i++)
        {
            printf("| %d >> %d ", i + 1, (int)get_list(q2, i));
            usq2 = userSet_id_lookup(com, get_list(q2, i));
            printf(" \t %d \n", getU_A(usq2) + getU_Q(usq2));
        }
        free_list(q2);
    }

    printf("______________________\n");
    printf("|->Q3\n\n");

    q3 = total_posts(com, begin, end);

    printf("from :: 16 - 01 - 2011\n");
    printf("to   :: 03 - 03 - 2013\n");

    printf("Number of Questions ::\t %ld \n", get_fst_long(q3));
    printf("Number of Answers   ::\t %ld \n", get_snd_long(q3));
    free_long_pair(q3);

    printf("______________________\n");
    printf("|->Q4\n\n");

    q4 = questions_with_tag(com, "google", begin, end);
    printf(" %d \n", get_size_list(q4));

    for (i = 0; i < get_size_list(q4); i++)
    {
        q6p = postSet_lookup(com, get_list(q4, i));
        pdate = getP_date(q6p);

        printf(" %d- %d- %d \n", get_day(pdate), get_month(pdate), get_year(pdate));

    }

    printf("______________________\n");
    printf("|->Q5\n\n");
    q5 = get_user_info(com, 16575);
    if (q5)
    {
        tmp = get_bio(q5);
        printf("Short user bio :: \n%s \n", tmp);
        printf("Last 10 posts  :: \n");

        l = get_10_latest_posts(q5);

        for (i = 0; i < 10; i++)
        {
            if (l[i])
            {
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
    else
        printf(" Nao existe colega! \n");

    printf("______________________\n");
    printf("|->Q6\n\n");

    n = 50;
    q6 = most_voted_answers(com, n, begin, end);
    if (q6)
    {
        for (i = 0; i < n; i++)
        {

            if ((unsigned int)get_list(q6, i))
            {
                printf(">> %d   ", (int)get_list(q6, i));
                q6p = postSet_lookup(com, (unsigned int)get_list(q6, i));
                printf("\t < %d > \n", getP_votes(q6p));
            }
            else
                printf(" Can't find that post bro\n");
        }
    }

    g_free(q6);

    printf("______________________\n");
    printf("|->Q7\n\n");
    n = 10;
    q7 = most_answered_questions(com, n, begin, end);

    if (q7)
    {
        for (i = 0; i < n; i++)
        {

            if ((unsigned int)get_list(q7, i))
            {
                printf(">> %d   ", (int)get_list(q7, i));
                q7p = postSet_lookup(com, (unsigned int)get_list(q7, i));
                printf("\t < %d > \n", getP_ansCount(q7p));
            }
            else
                printf(" Can't find that post bro\n");
        }
    }
    g_free(q7);

    printf("______________________\n");
    printf("|->Q8\n\n");
    n = 40;
    q8 = contains_word(com, "PLAY", n);
    if (q8)
    {
        for (i = 0; i < n; i++)
        {
            if ((unsigned int)get_list(q8, i))
            {
                q8p = postSet_lookup(com, (unsigned int)get_list(q8, i));
                pdate = getP_date_point(q8p);
                if (q8p)
                    printf(" %d ||  %d-%d-%d || \t name : : %s || \n", i + 1, get_day(pdate), get_month(pdate), get_year(pdate), getP_name_point(q8p));
            }
        }
    }
    g_free(q8);
    printf("______________________\n");
    printf("|->Q9\n\n");
    n = 10;
    q9 = both_participated(com, 5342, 16575, n);
    if (q9)
    {
        for (i = 0; i < n; i++)
        {

            if ((unsigned int)get_list(q9, i))
            {
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

    printf("______________________\n");
    printf("|->Q10\n\n");

    q10 = better_answer(com, 35580);
    if (q10)
    {

        printf("----1>| %ld |<1----\n", q10);
        //g_free(q10);
        q9p = postSet_lookup(com, (unsigned long)q10);

        printf(" ----1>| votes _%d ! comment _%d ! score _%d ! \n", (int)getP_votes(q9p), (int)getP_nComment(q9p), (int)getP_score(q9p));
    }

    printf("______________________\n");
    printf("|->Q11\n\n");

    n = 10;
    q11 = most_used_best_rep(com, n, begin, end);
    if (q11)
    {
        for (i = 0; i < n; i++)
            if (get_list(q11, i))
            {
                printf(">> %d  || %ld \n", (int)i + 1, get_list(q11, i));
            }
        g_free(q11);
    }

    g_free(begin);
    g_free(end);
    clean(com);
    return 1;
}
*/
//#include "Bloco.h"
//#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include "Community.h"
#include <stdio.h>
//#include "interface.h"

// macros
#define inc_fst_long(x) set_fst_long(x, 1 + get_fst_long(x))
#define inc_snd_long(x) set_snd_long(x, 1 + get_snd_long(x))

// Métodos publicos.
STR_pair info_from_post(TAD_community com, int id);                                //#1
LONG_pair total_posts(TAD_community com, Date begin, Date end);                    //#3
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end);      //#6
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end); //#7

// Métodos privados-->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

static void count(void *value, void *user_data)
{
    LONG_pair k = (LONG_pair)user_data;
    Post p = (Post)value;

    if (getP_type(p) == 1)
        inc_fst_long(k); // é Questão.
    else
        inc_snd_long(k); // não é Questão.
}

static int is_A(void *value, void *user_data)
{
    return (2 == getP_type((Post)value));
}

static int is_Q(void *value, void *user_data)
{

    return (1 == getP_type((Post)value));
}

// -- 1 FEITO
STR_pair info_from_post(TAD_community com, int id)
{
    unsigned char *str1, *str2;
    Util y = NULL;
    Post x = NULL;
    STR_pair result;
    unsigned long userid;
    if (is_ON(com))
    {
        x = postSet_lookup(com, id);
        if (!x)
        {
            return create_str_pair("", "");
        }

        str1 = getP_name(x);
        userid = getP_fund(x);

        y = userSet_id_lookup(com, userid);
        if (!y)
        {
            g_free(str1);
            return create_str_pair((char *)str1, "");
        }
        str2 = getU_name(y);
        result = create_str_pair((char *)str1, (char *)str2);

        g_free(str1);
        g_free(str2);

        return result;
    }
    else
        return NULL;
}

// --3 FEITO   ->
LONG_pair total_posts(TAD_community com, Date begin, Date end)
{
    if (is_ON(com))
        return (LONG_pair)arraySeg_transversal(com, begin, end, count, (void *)create_long_pair(0, 0));
    else
        return NULL;
}

// --6 FEITA
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end)
{
    unsigned long i;
    LONG_list ll;
    Post newp;
    HEAP x; //
    if (is_ON(com))
    {
        x = arraySeg_Priority_Queue(com, begin, end, (unsigned long)N, score_cmp, is_A, NULL);

        ll = create_list(N);

        for (i = 0; i < N; i++)
        {
            if (!empty_H(x))
            {
                newp = (Post)rem_Heap(x);
                set_list(ll, N - 1 - i, (long)getP_id(newp));
            }
            else
            {
                set_list(ll, N - 1 - i, 0);
            }
        }

        destroy_H(x);
        return ll;
    }
    return NULL;
}

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end)
{
    unsigned long i;
    LONG_list ll;
    Post newp;
    HEAP x; //
    if (is_ON(com))
    {
        x = arraySeg_Priority_Queue(com, begin, end, (unsigned long)N, nAns_cmp, is_Q, NULL);

        ll = create_list(N);

        for (i = 0; i < N; i++)
        {
            if (!empty_H(x))
            {
                newp = (Post)rem_Heap(x);
                set_list(ll, N - 1 - i, (long)getP_id(newp));
            }
            else
            {
                set_list(ll, N - 1 - i, 0);
            }
        }

        destroy_H(x);
        return ll;
    }
    else
        return NULL;
}

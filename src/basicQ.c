
#include <glib.h>
#include <string.h>
#include "Community.h"
#include <stdio.h>
#include <comondec.h>
#include <ctype.h>
#include <bArray.h>

//-------------------------------------------------------------------------------------

// defines
#define inc_fst_long(x) set_fst_long(x, 1 + get_fst_long(x))
#define inc_snd_long(x) set_snd_long(x, 1 + get_snd_long(x))

// Métodos publicos.
STR_pair info_from_post(TAD_community com, int id);                                //#1
LONG_pair total_posts(TAD_community com, Date begin, Date end);                    //#3
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end);      //#6
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end); //#7
LONG_list contains_word(TAD_community com, char *word, int N);                     //#8

// Métodos privados.
static int match(void *value, void *user_data);
static void count(void *value, void *user_data);

//-------------------------------------------------------------------------------------

static int match(void *value, void *user_data)
{
    Record bx = (Record)user_data;
    Record cur = (Record)bx->snd;
    Record count = (Record)cur->fst;

    char *word = (char *)bx->fst;
    char *title, *org, *x;

    int lenz;
    LONG_list k = (LONG_list)cur->snd;
    int *index = (int *)count->fst;
    int size = *(int *)count->snd;

    org = (char *)getP_name_point((Post)value);
    if (org)
    {
        lenz = (strlen(org) + 3);
        title = g_malloc(sizeof(char) * lenz);

        *title = ' ';
        strcpy(title + 1, org);
        title[lenz - 1] = '\0';
        title[lenz - 2] = ' ';

        for (x = title; *x; x++)
            *x = tolower(*x);

        if ((getP_type((Post)value) == 1))
        {

            if (strstr(title, word))
            {
                set_list(k, *index, getP_id(value));
                *index += 1;
            }
        }

        g_free(title);
    }
    return (*index != size);
}

static void count(void *value, void *user_data)
{
    LONG_pair k = (LONG_pair)user_data;
    Post p = (Post)value;

    if (getP_type(p) == 1)
        inc_fst_long(k); // é Questão.
    else
        inc_snd_long(k); // não é Questão.
}

//-------------------------------------------------------------------------------------

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
            create_str_pair(NULL, NULL);

        if (getP_type(x) == 2)
        {
            x = postSet_lookup(com, getP_parentId(x));
            if (!x)
                return create_str_pair(NULL, NULL);
        }
        str1 = getP_name(x);
        userid = getP_fund(x);

        y = userSet_id_lookup(com, userid);
        if (!y)
        {
            g_free(str1);
            return create_str_pair((char *)str1, NULL);
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

LONG_pair total_posts(TAD_community com, Date begin, Date end)
{
    if (is_ON(com))
        return (LONG_pair)arraySeg_transversal(com, begin, end, count, (void *)create_long_pair(0, 0));
    else
        return NULL;
}

LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end)
{
    unsigned long i;
    LONG_list ll;
    Post newp;
    HEAP x; //
    if (is_ON(com))
    {
        x = arraySeg_Priority_Queue(com, begin, end, (unsigned long)N, votes_cmp, is_A, NULL);

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

LONG_list contains_word(TAD_community com, char *word, int N)
{
    int index = 0; // ( list , ( ( &index , &size ) , word) )
    int i;
    Record y, x;
    char *cur, *wordcpy;
    LONG_list ll;
    if (is_ON(com))
    {
        wordcpy = g_malloc(sizeof(char *) * (strlen(word) + 3));
        ll = create_list(N);
        sprintf(wordcpy, " %s ", word);

        for (cur = wordcpy; *cur; cur++)
            *cur = tolower(*cur);

        x = createRecord(wordcpy, createRecord(createRecord(&index, &N), ll));

        x = arrayRev_transversal(com, match, x);
        if (index >= 0)
        {
            for (i = index; i < N; i++)
            { //caso não haja N match's.

                set_list(ll, i, 0);
            }
        }
        y = x->snd;

        g_free(y->fst);
        g_free(y);
        g_free(x);
        g_free(wordcpy);
        return (ll);
    }
    else
        return NULL;
}

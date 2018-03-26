//#include "Bloco.h"
//#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include "Community.h"
#include <stdio.h>
#include <comondec.h>
#include <ctype.h>
//#include "interface.h"

#include <bArray.h>

// macros
#define inc_fst_long(x) set_fst_long(x, 1 + get_fst_long(x))
#define inc_snd_long(x) set_snd_long(x, 1 + get_snd_long(x))

// Métodos publicos.
STR_pair info_from_post(TAD_community com, int id);             //#1
LONG_list top_most_active(TAD_community com, int N);            //#2
LONG_pair total_posts(TAD_community com, Date begin, Date end); //#3

USER get_user_info(TAD_community com, long id);                                    //#5
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end);      //#6
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end); //#7
LONG_list contains_word(TAD_community com, char *word, int N);                     //#8

// Métodos privados-->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
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

static void collect_top10(void *key, void *value, void *user_data)
{

    unsigned long *parent = (unsigned long *)key;
    unsigned long *child = (unsigned long *)value;
    unsigned long *used;

    Record carrier = (Record)user_data;
    Record rd = (Record)carrier->fst;
    char *flag = (char *)carrier->snd;

    TAD_community com = (TAD_community)rd->snd;

    bArray rd1;
    HEAP rd2;
    Post pub;

    if (child)
    {
        // é uma resposta.
        used = child;
    }
    else
    {
        // é uma questão.
        used = parent;
    }

    pub = postSet_lookup(com, *used);

    if (!*flag)
    { //barray
        rd1 = (bArray)rd->fst;
        if (!is_full(rd1))
        { //não está cheio o array
            rd1 = add_to_A(rd1, pub);
        }
        else
        { // está cheio o array
            rd2 = Generalized_Priority_Queue(rd1, length_A(rd1), post_compare, yes, NULL);
            destroy_A(rd1);
            *flag = 1;
            rd->fst = rd2;
        }
    }
    else
    { //heap

        rd2 = (HEAP)rd->fst;
        rd2 = add_in_Place_H(rd2, pub);
    }
}

static void make_pq(void *key, void *value, void *user_data)
{
    Record x = (Record)user_data;
    char *flag = (char *)(x->snd);
    bArray rd1;
    HEAP rd2;

    if (!*flag)
    { // ainda está no array.
        rd1 = (bArray)x->fst;
        if (!is_full(rd1))
        { //não está cheio o array
            rd1 = add_to_A(rd1, value);
        }
        else
        { // está cheio o array
            rd2 = Generalized_Priority_Queue(rd1, length_A(rd1), np_cmp, yes, NULL);
            destroy_A(rd1);
            *flag = 1;
            x->fst = rd2;
        }
    }
    else
    { // já está na heap.
        rd2 = (HEAP)x->fst;
        rd2 = add_in_Place_H(rd2, value);
    }
}

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
            return create_str_pair("", "");

        if (getP_type(x) == 2)
        {
            x = postSet_lookup(com, getP_parentId(x));
            if (!x)
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

USER get_user_info(TAD_community com, long id)
{
    char *flag = g_malloc(sizeof(char));
    HEAP hp;
    bArray extreme;

    long post_history[10];
    char *short_bio = NULL;
    int i;

    Post the_post;
    USER send;
    Util x;
    Record rd, carrier;

    *flag = 0;
    if (is_ON(com))
    {
        carrier = createRecord(createRecord((void *)init_A(10, NULL), (void *)com), (void *)flag); // usar post compare.

        x = userSet_id_lookup(com, (unsigned long)id);

        if (!x)
        {
            for (i = 0; i < 10; i++)
                post_history[i] = 0;

            rd = (Record)carrier->fst;
            destroy_A(rd->fst);
            g_free(carrier->fst);
            g_free(flag);
            g_free(carrier);
            return create_user("", post_history);
        }
        short_bio = (char *)getU_bio(x);

        if (!short_bio)
        {
            short_bio = g_malloc(sizeof(char));
            *short_bio = '\0';
        }

        // x->bio;
        carrier = toBacia_transversal(x, collect_top10, carrier); //

        rd = (Record)carrier->fst;

        if ((*(char *)carrier->snd) == 1)
        {
            hp = (HEAP)rd->fst;
        }
        else
        {
            extreme = (bArray)rd->fst;
            hp = Generalized_Priority_Queue(extreme, length_A(extreme), post_compare, yes, NULL);
            destroy_A(extreme);
        }
        //->>>>

        for (i = 0; i < 10; i++)
        { // vai do novo para o velho. (cronologia inversa)

            if (!empty_H(hp))
            {

                the_post = (Post)rem_Heap(hp);
                post_history[i] = (long)getP_id(the_post);
            }
            else
            {
                post_history[i] = 0;
            }
        }

        send = create_user(short_bio, post_history);

        g_free(short_bio);
        g_free(flag);

        g_free(carrier->fst);
        g_free(carrier);

        destroy_H(hp);

        return send;
    }
    else
        return NULL;
}

LONG_list top_most_active(TAD_community com, int N)
{
    unsigned long i;
    char *flag;
    Record x;
    LONG_list ll = NULL;
    Util c;
    HEAP hp;
    bArray extreme;
    if (is_ON(com))
    {
        flag = g_malloc(sizeof(char));
        *flag = 0;
        x = createRecord(init_A((unsigned long)N, NULL), flag);

        x = userSet_id_transversal(com, make_pq, (void *)x);
        ll = create_list(N);
        //

        if ((*(char *)x->snd) == 1)
        {
            hp = (HEAP)x->fst;
        }
        else
        {
            extreme = (bArray)x->fst;
            hp = Generalized_Priority_Queue(extreme, length_A(extreme), np_cmp, yes, NULL);
            destroy_A(extreme);
        }

        //x contem    se x->snd ==1  HEAP
        //x contem    se x->snd ==0  bArray
        //

        for (i = 0; i < N; i++)
        {

            if (!empty_H(hp))
            {

                c = rem_Heap(hp);
                set_list(ll, N - 1 - i, (long)getU_id(c));
            }
            else
            {
                set_list(ll, i, 0);
            }
        }

        g_free(flag);
        g_free(x);
        destroy_H(hp);
    }
    return ll;
}

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

    x = postSet_lookup(com, id);
    if (!x)
        return NULL;

    str1 = getP_name(x);
    userid = getP_fund(x);

    y = userSet_id_lookup(com, userid);
    if (!y)
        return NULL;

    str2 = getU_name(y);
    result = create_str_pair((char *)str1, (char *)str2);

    g_free(str1);
    g_free(str2);

    return result;
}

// recebe uma avl tree e retira de la as datas , para um su-array defenido no glib
// estou a assumir que recebo uma AVL;

// --3 FEITO   ->
LONG_pair total_posts(TAD_community com, Date begin, Date end)
{
    return (LONG_pair)arraySeg_transversal(com, begin, end, count, (void *)create_long_pair(0, 0));
}

// --6 FEITA
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end)
{
    unsigned long i;
    LONG_list ll;
    Post newp;
    HEAP x; //

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

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end)
{
    unsigned long i;
    LONG_list ll;
    Post newp;
    HEAP x; //

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
// VERIFICAR SE O MORE_ANSWER ESTA CERTOOOOOOOOOOOOOOOOO'O''O'O'O'OO''O'O'O'O'O'O'O'O'O'O'O'O'O'O'O'O'
// VERIFICAR SE O MORE_ANSWER ESTA CERTOOOOOOOOOOOOOOOOO'O''O'O'O'OO''O'O'O'O'O'O'O'O'O'O'O'O'O'O'O'O'
// --7 FALTA ACABAR
/*
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
    int num;
    LONG_list lista = create_list(N);
    Post p = NULL;

    Container carrier = createContainer(begin,end);
    carrier->spec = (void*)limcreate_H (N,NULL);

    postTree_transversal (com , more_answer , (void*) carrier );
    // ja me mete em ordem decrescente
    while(N>0){
        p = (Post)rem_Heap( (HEAP)carrier->spec ,&num);
        set_list(lista, N , getP_id (p))  ;
        N++;
    }
    destroy_H (carrier->spec);
    g_free(carrier);
    destroyPost(p);

    return lista;
}
*/

/*
}

// --8 FALTA ACBABAR
LONG_list contains_word(TAD community com, char* word, int N){
    LONG_list lista = create_list (N);

}


*/

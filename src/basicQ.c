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

// Estruturas privadas
typedef struct contain
{
    Date dateB;
    Date dateE;
    void *spec;
} * Container;
//

// Métodos publicos.
STR_pair info_from_post(TAD_community com, int id);                           //#1
LONG_pair total_posts(TAD_community com, Date begin, Date end);               //#3
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end); //#6

// Métodos privados-->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

static Container createContainer(Date begin, Date end)
{

    Container x = g_malloc(sizeof(struct contain));
    x->dateB = begin;
    x->dateE = end;
    x->spec = NULL;
    return x;
}

static void count(void *value, void *user_data)
{

    Date x = (Date)getP_date_point((Post)value);
    Container box = (Container)user_data;
    LONG_pair k = (LONG_pair)box->spec;
    Post p = (Post)value;
    /*
    Se as datas forem iguais e tipo for 1 (quest) aumenta as quest e vice-versa para as respostas
    compara atraves do data_compare -> data.h
    */

    if (date_compare(x, box->dateB, NULL) >= 0 && date_compare(x, box->dateE, NULL) <= 0)
    {
        //printf(" %d  \n",(int) getP_score(p));
        if (getP_type(p) == 1)
            inc_fst_long(k); // é Questão.
        else
            inc_snd_long(k); // não é Questão.
    }

}

static int is_A(void *value, void *user_data)
{

    return (2 == getP_type((Post)value));
}

/*
static int more_answer ( void *key , void*value , void* user_data ){

    Container box = (Container) user_data;
    HEAP x = (HEAP)box->spec;
    Post post = (Post)value;
    int num = 0;//getP_answers(post);


    if ( date_compare ( box->dateB , (Date) key ,NULL) >= 0 && date_compare ( box->dateE, (Date) key,NULL ) <= 0 && getP_type(post) == 2 ){// é resposta.
        if ( maxQ_H (x) )// se está na capacidade
            addR_Heap( x , (-1) * num , post );
        else 
            add_Heap( x , (-1) * num , post  );
        }

    // The tree is traversed in sorted order.
    if ( date_compare ( x , box->dateE , NULL )>0 )
        return 1;
    return 0;

}
*/

//->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// -- 1 FEITO
STR_pair info_from_post(TAD_community com, int id)
{
    unsigned char *str1, *str2;
    Util y = NULL;
    Post x = NULL;
    STR_pair result;
    unsigned long userid;

    x = postSet_lookup(com, id);
    if( !x )
        return NULL;
    
    str1 = getP_name(x);
    userid = getP_fund(x);

    y = userSet_id_lookup(com, userid);
    if( !y )
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

    Container x = createContainer(begin, end); //set_snd_long
    x->spec = (void *)create_long_pair(0, 0); 

    // nao esta defenido por incompetencia (LONG_PAIR) xD !!!!!!!!!!!!!!!!!!!!!!!!!!!!

    //post_compare

    x = arraySeg_transversal(com, begin , end , count, (void *)x);

    LONG_pair res = (LONG_pair)x->spec;

    g_free(x);

    return res;
}

// --6 FEITA
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end)
{
    unsigned long i;
    LONG_list ll;
    Date d;
    Post newp;
    HEAP x; //

    x = arraySeg_Priority_Queue(com, begin, end, (unsigned long)N, score_cmp, is_A, NULL);

    ll = create_list(N);

    for (i = 0; i < N; i++)
    {
        if (!empty_H(x))
        {
            newp = (Post)rem_Heap(x);
            //printf("num :: %d\n",num);
            d = getP_date_point(newp);

            if (date_compare(d, begin, NULL) >= 0 && date_compare(d, end, NULL) <= 0) // no futuro poderá ser removida. <assim que o find for melhorado>
                set_list(ll, N - 1 - i , (long)getP_id(newp));
        }
        else
        {
            set_list(ll,  N - 1 - i, 0);
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

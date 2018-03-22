#include <glib.h>
#include <string.h>
#include "Community.h"

#include "bArray.h"

// Estruturas  privadas
typedef struct record
{
    void *fst;
    void *snd;
} * Record;
/////

// Métodos Publicos
USER get_user_info(TAD_community com, long id);      //#5
LONG_list top_most_active(TAD_community com, int N); //#2

// Métodos Privados.
static Record createRecord(void *fs, void *sn)
{
    Record a = g_malloc(sizeof(struct record));
    a->fst = fs;
    a->snd = sn;
    return a;
}

static int yes(void *a, void *b)
{
    return 1;
}


static void collect_top10(void *key, void *value, void *user_data)
{

    unsigned long *parent = (unsigned long *)key;
    unsigned long *child = (unsigned long *)value;
    unsigned long *used;

    Record carrier = (Record)user_data;
    Record rd = (Record)carrier->fst;
    char* flag = (char*)carrier->snd;

    TAD_community com = (TAD_community)rd->snd;

    bArray rd1;
    HEAP   rd2;
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

    if( ! *flag ){//barray
        rd1 = (bArray)rd->fst;
        if (!is_full(rd1))
        { //não está cheio o array
            add_to_A(rd1, pub);
        }
        else
        { // está cheio o array
            rd2 = Generalized_Priority_Queue(rd1, length_A(rd1), post_compare, yes, NULL);
            destroy_A(rd1);
            *flag = 1;
            rd->fst = rd2;
        }
    } else {//heap

        rd2 = (HEAP)rd->fst;
        add_in_Place_H(rd2, pub);

    }
}

////////
/*
USER get_user_info(TAD_community com, long id)
{
    int i;
    Post the_post;
    USER send;
    Record carrier;
    HEAP pQ = create_H(NULL, reverseCompare, (void *)post_compare);
    long post_history[10];
    char *short_bio = NULL;
    Util x = userSet_id_lookup(com, (unsigned long)id);

    if (!x)
        return NULL;
    short_bio = (char *)getU_bio(x);

    carrier = createRecord((void *)pQ, (void *)com);
    // x->bio;
    toBacia_transversal(x, collect_top10, carrier);

    //

    for (i = 0; i < 10; i++)
    { // vai do novo para o velho. (cronologia inversa)

        if (!empty_H(pQ))
        {

            the_post = (Post)rem_Heap(pQ);
            post_history[i] = (long)getP_id(the_post);
        }
        else
        {

            post_history[i] = 0;
        }
    }

    send = create_user(short_bio, post_history);

    g_free(short_bio);
    g_free(carrier);
    destroy_H(pQ);
    return send;
}
*/

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
            add_to_A(rd1, value);
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
        add_in_Place_H(rd2, value);
    }
}
// --2 FEITO
LONG_list top_most_active(TAD_community com, int N)
{
    unsigned long i;
    char *flag = g_malloc(sizeof(char));
    Record x;
    LONG_list ll;
    Util c;
    HEAP hp;
    bArray extreme;

    *flag = 0;
    x = createRecord(init_A((unsigned long)N, NULL), flag);

    userSet_id_transversal(com, make_pq, (void *)x);
    ll = create_list(N);
    //

    if( (*(char*)x->snd) == 1 ){
        hp = (HEAP)x->fst;

    } else {
        extreme = (bArray)x->fst;
        hp = Generalized_Priority_Queue( extreme , length_A(extreme), np_cmp, yes, NULL);
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
            set_list(ll, i, (long)getU_id(c));
        }
        else
        {
            set_list(ll, i, 0);
        }
    }
    
    g_free(x->snd);
    g_free(x);
    destroy_H(hp);

    return ll;
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
    Record rd;

    *flag = 0;

    Record carrier= createRecord( createRecord( (void*)init_A(10, NULL) , (void *)com) , (void*)flag);// usar post compare.
    
    Util x = userSet_id_lookup(com, (unsigned long)id);

    if (!x)
        return NULL;
    
    short_bio = (char *)getU_bio(x);

    // x->bio;
    toBacia_transversal(x, collect_top10, carrier);//

    rd = (Record)carrier->fst;

    if( (*(char*)carrier->snd) == 1 ){    
        hp = (HEAP)rd->fst;

    } else {
        extreme = (bArray)rd->fst;
        hp = Generalized_Priority_Queue( extreme , length_A(extreme), post_compare, yes, NULL);
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

    g_free(carrier->fst);
    g_free(carrier);
    
    destroy_H(hp);

    return send;
}
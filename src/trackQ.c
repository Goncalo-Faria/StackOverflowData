#include <glib.h>
#include <string.h>
#include "Community.h"

#include "bArray.h"

#include <stdio.h>
#include <comondec.h>

// Métodos publicos.
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end); //#11
LONG_list top_most_active(TAD_community com, int N);                          //#2
USER get_user_info(TAD_community com, long id);                               //#5

// Métodos privados.
static void get_active(void *key, void *value, void *user_data);
static void collect_top10(void *key, void *value, void *user_data);
static void gather_rep(void *key, void *value, void *user_data);
static void make_histogram(void *key, void *value, void *user_data);
static void tag_count_free(void *y);
static void fil_hash(void *b, void *user_data);
static void hist_tag(unsigned int tag, void *user_data);
static void *standart_make_pq(void (*freeCap)(void *), void *value, void *user_data, int (*Hcmp)(void *, void *, void *));

//-------------------------------------------------------------------------------------
// ( NULL , value , user_data, rep_cmp )
static void gather_rep(void *key, void *value, void *user_data)
{
    user_data = standart_make_pq(NULL, value, user_data, rep_cmp);
}
// Post  // data

static void hist_tag(unsigned int tag, void *user_data)
{

    int *c;
    int *key;
    GHashTable *htable_tag = (GHashTable *)user_data;

    if (g_hash_table_contains(htable_tag, &tag))
    {
        c = g_hash_table_lookup(htable_tag, &tag);
        *c += 1;
    }
    else
    {
        c = g_malloc(sizeof(int));
        key = g_malloc(sizeof(unsigned int));
        *c = 1;
        *key = tag;

        g_hash_table_insert(htable_tag, key, c);
    }
}

static void collect_top10(void *key, void *value, void *user_data)
{

    unsigned long *parent = (unsigned long *)key;
    unsigned long *child = (unsigned long *)value;
    unsigned long *used;

    Record carrier = (Record)user_data;
    Record rd = (Record)carrier->fst;

    TAD_community com = (TAD_community)carrier->snd;

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

    if (pub)
        rd = standart_make_pq(NULL, pub, rd, post_compare);
}

static void fil_hash(void *b, void *user_data)
{
    Post p = (Post)b;
    unsigned long f = getP_fund(p);
    Record x = (Record)user_data;
    GHashTable *htable_usr = (GHashTable *)x->fst;
    GHashTable *htable_tag = (GHashTable *)x->snd;

    if (g_hash_table_contains(htable_usr, &f))
    {
        htable_tag = postTag_transversal(p, hist_tag, htable_tag);
    }
}

static void tag_count_free(void *y)
{
    Record x = (Record)y;
    g_free(x->snd);
    g_free(x->fst);
    g_free(x);
}

// ( tag_count_free, createRecord(key, value) , user_data, tag_count_cmp )
static void make_histogram(void *key, void *value, void *user_data)
{
    user_data = standart_make_pq(tag_count_free, createRecord(key, value), user_data, tag_count_cmp);
}

static void *standart_make_pq(void (*freeCap)(void *), void *value, void *user_data, int (*Hcmp)(void *, void *, void *))
{

    Record carrier = (Record)user_data;
    Record rd = (Record)carrier->fst;
    char *flag = (char *)carrier->snd;
    int sig = 0;
    bArray rd1;
    HEAP rd2;

    if (!*flag)
    { //barray
        rd1 = (bArray)rd->fst;
        if (!is_full(rd1))
        { //não está cheio o array
            rd1 = add_to_A(rd1, value);
        }
        else
        { // está cheio o array
            rd2 = Generalized_Priority_Queue(rd1, length_A(rd1), Hcmp, yes, NULL);
            destroy_A(rd1);
            *flag = 1;

            rd2 = add_in_Place_H_signal(rd2, value , &sig);
            if (!sig)
                if (freeCap)
                    freeCap(value);

            rd->fst = rd2;
        }
    }
    else
    { //heap

        rd2 = (HEAP)rd->fst;
        rd2 = add_in_Place_H_signal(rd2, value, &sig);

        if (!sig)
            if (freeCap)
                freeCap(value);
    }
    return user_data;
}

static void get_active(void *key, void *value, void *user_data)
{
    // ( NULL, value , user_data, np_cmp )
    user_data = standart_make_pq(NULL, value, user_data, np_cmp);
}

LONG_list top_most_active(TAD_community com, int N)
{
    unsigned long i;
    char flag;
    Record x;
    LONG_list ll = NULL;
    Util c;
    HEAP hp;
    bArray extreme;
    if (is_ON(com))
    {
        flag = 0;
        x = createRecord(init_A((unsigned long)N, NULL), &flag);

        x = userSet_id_transversal(com, get_active, (void *)x);
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

        g_free(x);
        destroy_H(hp);
    }
    return ll;
}

LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end)
{
    HEAP hp;
    GHashTable *htable_usr, *htable_tag;
    Util cur;
    //bArray extreme;
    Record x;
    LONG_list ll;
    int flag;
    long i;

    if (is_ON(com))
    {
        flag = 0;

        x = userSet_id_transversal(com, gather_rep, (void *)createRecord(init_A((unsigned long)N, NULL), &flag));

        htable_usr = g_hash_table_new_full(g_int64_hash, g_int64_equal, NULL, NULL);
        htable_tag = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, NULL);

        if (flag)
        {
            hp = (HEAP)x->fst;
            g_free(x);

            while (!empty_H(hp))
            {
                cur = (Util)rem_Heap(hp);
                g_hash_table_insert(htable_usr, getU_id_point(cur), cur);
            }
            destroy_H(hp);

            x = arraySeg_transversal(com, begin, end, fil_hash, createRecord(htable_usr, htable_tag));

            g_free(x);
            g_hash_table_destroy(htable_usr);

            // > ha um erro a gerir memória.
            flag = 0;
            x = createRecord(init_A(N, NULL), &flag);
            g_hash_table_foreach(htable_tag, make_histogram, x);
            if (flag)
            { // tudo na heap.
                hp = (HEAP)x->fst;
                g_hash_table_destroy(htable_tag);
                g_free(x);

                N = length_H(hp);
                ll = create_list(N);

                while (!empty_H(hp))
                {
                    x = (Record)rem_Heap(hp);

                    i = (long)x->fst;
                    if (x)
                    {
                        set_list(ll, --N, (long)i);
                        tag_count_free(x);
                    }
                    else
                        set_list(ll, --N, 0);
                }
            }
        }
        //else
        return ll;
    }
    else
        return NULL;
}

USER get_user_info(TAD_community com, long id)
{
    char flag;
    HEAP hp;
    bArray extreme;

    long post_history[10];
    char *short_bio = NULL;
    int i;

    Post the_post;
    USER send;
    Util x;
    Record rd, carrier;

    flag = 0;
    if (is_ON(com))
    {
        carrier = createRecord(createRecord((void *)init_A(10, NULL), (void *)&flag), (void *)com); // usar post compare.

        x = userSet_id_lookup(com, (unsigned long)id);

        if (!x)
        {
            for (i = 0; i < 10; i++)
                post_history[i] = 0;

            rd = (Record)carrier->fst;
            destroy_A(rd->fst);
            g_free(carrier->fst);
            g_free(carrier);
            return NULL;
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

        g_free(carrier->fst);
        g_free(carrier);

        destroy_H(hp);

        return send;
    }
    else
        return NULL;
}
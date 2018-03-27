#include <glib.h>
#include <string.h>
#include "Community.h"

#include "bArray.h"
#include <stdio.h>
#include <comondec.h>

// Estruturas  privadas

struct no
{
    unsigned int pid;
    struct no *px;
};

typedef struct bo
{
    float key;
    Post pid;

} * Box;

/////

// Métodos Publicos
LONG_list both_participated(TAD_community com, long id1, long id2, int N);    //#9
LONG_list better_answer(TAD_community com, int id);                           //#10
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end); //#11

// Métodos Privados.

static Box createBox(float key, Post pid)
{
    Box send = g_malloc(sizeof(struct bo));

    send->key = key;
    send->pid = pid;
    return send;
}
static float rank(TAD_community com, Post x) //x
{
    float r;
    unsigned long founder;
    Util u;
    float rep, fav, cmm, scr;

    founder = getP_fund(x);
    if (founder)
    {
        u = userSet_id_lookup(com, founder);
        if (u)
        {
            rep = (float)getU_rep(u);
            fav = (float)getP_votes(x);
            cmm = (float)getP_nComment(x);
            scr = (float)getP_score(x);

            r = rep * 0.25 + fav * 0.2 + cmm * 0.1 + scr * 0.45;
        }
        else
        {
            r = 0;
        }
    }
    else
    {
        r = 0;
    }

    return r;
}
static void intr(void *key, void *value, void *user_data)
{
    Record box = (Record)user_data;
    Record ll = (Record)box->fst;
    int *counter = (int *)ll->snd;
    struct no **cur = (struct no **)ll->fst;
    struct no *new;
    Util lrg = (Util)box->snd;
    unsigned int pst = *(unsigned int *)key;

    if (toBacia_contains(lrg, pst))
    {

        new = g_malloc(sizeof(struct no));
        new->pid = pst;
        new->px = *cur;
        *cur = new;
        *counter += 1;
    }
}

static void *travel(Post x, void *user_data)
{
    Record cur = (Record)user_data;
    TAD_community com = (TAD_community)cur->fst;
    Box a = (Box)cur->snd;
    float r;

    r = rank(com, x);

    if (a)
    {
        if (r > a->key)
        {
            a->key = r;
            a->pid = x;
        }
    }
    else
    {
        cur->snd = createBox(r, x);
    }

    return (void *)cur;
}

LONG_list both_participated(TAD_community com, long id1, long id2, int N)
{

    Util usr1, usr2;
    int p, pred, req = N;
    Record box;
    Util sml, lgr;
    HEAP hp;
    bArray b;
    Post u;
    struct no *del, *x, *cur = NULL;

    LONG_list ll;
    if (is_ON(com))
    {
        usr1 = userSet_id_lookup(com, id1);
        usr2 = userSet_id_lookup(com, id2);

        if (usr1 && usr2)
        {
            p = toBacia_size(usr1) > toBacia_size(usr2);

            sml = p ? usr2 : usr1;
            lgr = p ? usr1 : usr2;
            p = 0;
            box = createRecord(createRecord(&cur, &p), lgr);
            box = toBacia_transversal(sml, intr, box);

            pred = (p < N);
            N = pred ? p : N;

            b = init_A((unsigned long)N, NULL);
            del = NULL;

            for (x = cur; N--; x = x->px)
            {

                if (del)
                    g_free(del);

                u = postSet_lookup(com, x->pid);
                if (u)
                    b = add_to_A(b, (void *)u);

                del = x;
            }

            if (del)
                g_free(del);

            if (!pred)
            { // ainda tem elementos a lista.
                hp = Generalized_Priority_Queue(b, length_A(b), inv_post_compare, yes, NULL);
                cur = x;
                ll = create_list(req);

                del = NULL;

                for (x = cur; x; x = x->px)
                {
                    if (del)
                        g_free(del);

                    u = postSet_lookup(com, x->pid);
                    if (u)
                        hp = add_in_Place_H(hp, u);

                    del = x;
                }
                if (del)
                    g_free(del);

                p = 0;
                N = length_H(hp);
                while (!empty_H(hp))
                {
                    u = rem_Heap(hp);
                    set_list(ll, N - 1 - p++, (long)getP_id(u));
                }

                for (p = p; p < req; p++)
                    set_list(ll, p, 0);

                destroy_H(hp);
            }
            else
            {
                b = sort_A(b, post_ord);
                N = length_A(b);
                ll = create_list(req);

                for (p = 0; p < N; p++)
                {
                    u = get_atA(b, p);
                    set_list(ll, N - 1 - p, (long)getP_id(u));
                }
                for (p = p; p < req; p++)
                    set_list(ll, p, 0);
            }
        }
        else
            return NULL;

        destroy_A(b);
        g_free(box->fst);
        g_free(box);

        return ll;
    }
    else
        return NULL;
}

LONG_list better_answer(TAD_community com, int id)
{
    Record a;
    Box bx;
    Post p = postSet_lookup(com, (unsigned int)id);
    LONG_list ll = create_list(1);

    if (is_ON(com))
    {
        if (p && (getP_type(p) == 1))
        {
            a = createRecord((void *)com, NULL);
            a = postAnswer_transversal(p, travel, a);

            bx = (Box)a->snd;

            if (bx)
                set_list(ll, 0, (long)getP_id(bx->pid));
            else
                set_list(ll, 0, 0);

            g_free(bx);
            g_free(a);
        }
        else
            set_list(ll, 0, 0);

        return ll;
    }
    else
        return NULL;
}

static void make_pq1(void *key, void *value, void *user_data)
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
            rd2 = Generalized_Priority_Queue(rd1, length_A(rd1), rep_cmp, yes, NULL);
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
static void make_pq2(void *key, void *value, void *user_data)
{
    Record x = (Record)user_data;
    char *flag = (char *)(x->snd);
    bArray rd1;
    HEAP rd2;
    int sig;

    if (!*flag)
    { // ainda está no array.
        rd1 = (bArray)x->fst;
        if (!is_full(rd1))
        { //não está cheio o array
            rd1 = add_to_A(rd1, createRecord(key, value));
        }
        else
        { // está cheio o array
            rd2 = Generalized_Priority_Queue(rd1, length_A(rd1), tag_count_cmp, yes, NULL);
            destroy_A(rd1);
            *flag = 1;
            x->fst = rd2;
        }
    }
    else
    { // já está na heap.
        rd2 = (HEAP)x->fst;
        x = createRecord(key, value);
        rd2 = add_in_Place_H_signal(rd2, x, &sig);

        if (!sig)
            tag_count_free(x);
    }
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

        x = userSet_id_transversal(com, make_pq1, (void *)createRecord(init_A((unsigned long)N, NULL), &flag));

        htable_usr = g_hash_table_new_full(g_int64_hash, g_int64_equal, NULL, NULL);
        htable_tag = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, NULL);

        if (flag)
        {
            hp = (HEAP)x->fst;
            while (!empty_H(hp))
            {
                cur = (Util)rem_Heap(hp);
                g_hash_table_insert(htable_usr, getU_id_point(cur), cur);
            }
            destroy_H(hp);
            g_free(x);

            x = arraySeg_transversal(com, begin, end, fil_hash, createRecord(htable_usr, htable_tag));

            g_free(x);
            g_hash_table_destroy(htable_usr);

            // > ha um erro a gerir memória.
            flag = 0;
            x = createRecord(init_A(N, NULL), &flag);
            g_hash_table_foreach(htable_tag, make_pq2, x);
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

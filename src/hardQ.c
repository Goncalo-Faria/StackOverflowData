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
LONG_list both_participated(TAD_community com, long id1, long id2, int N); //#9
LONG_list better_answer(TAD_community com, int id);                        //#10

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
            fav = (float)getP_fav(x);
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
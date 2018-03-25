#include <glib.h>
#include <string.h>
#include "Community.h"

#include "bArray.h"
#include <stdio.h>

// Estruturas  privadas
typedef struct record
{
    void *fst;
    void *snd;
} * Record;

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
LONG_list top_most_active(TAD_community com, int N);                       //#2
USER get_user_info(TAD_community com, long id);                            //#5
LONG_list both_participated(TAD_community com, long id1, long id2, int N); //#9
LONG_list better_answer(TAD_community com, int id);                        //#10

// Métodos Privados.
static Record createRecord(void *fs, void *sn)
{
    Record a = g_malloc(sizeof(struct record));
    a->fst = fs;
    a->snd = sn;
    return a;
}

static Box createBox(float key, Post pid)
{
    Box send = g_malloc(sizeof(struct bo));

    send->key = key;
    send->pid = pid;
    return send;
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

// --2 FEITO
LONG_list top_most_active(TAD_community com, int N)
{
    unsigned long i;
    char *flag;
    Record x;
    LONG_list ll = NULL;
    Util c;
    HEAP hp;
    bArray extreme;
    if (com)
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

    Record carrier = createRecord(createRecord((void *)init_A(10, NULL), (void *)com), (void *)flag); // usar post compare.

    Util x = userSet_id_lookup(com, (unsigned long)id);

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

static void *travel(Post x, void *user_data)
{
    Record cur = (Record)user_data;
    TAD_community com = (TAD_community)cur->fst;
    Box a = (Box)cur->snd;
    float r;

    printf(">> %d \n", (int)getP_id(x));
    r = rank(com, x);

    if (a)
    {
        if (r > a->key)
        {
            a->key = r;
            a->pid = x;

            //printf("\t %f :: %d  | \n",r,(int)getP_id(x));
        }
    }
    else
    {
        cur->snd = createBox(r, x);
    }

    return (void *)cur;
}

LONG_list better_answer(TAD_community com, int id)
{
    Record a;
    Box bx;
    Post p = postSet_lookup(com, (unsigned int)id);
    LONG_list ll = create_list(1);

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

static int match(void *value, void *user_data)
{
    Record bx = (Record)user_data;
    Record cur = (Record)bx->fst;
    Record count = (Record)cur->snd;

    LONG_list k = (LONG_list)cur->fst;
    int size = *(int *)count->fst;
    int *index = (int *)count->snd;
    char *nid = (char *)bx->snd;

    if (strstr((char *)getP_name_point((Post)value), nid))
    {
        set_list(k, *index, getP_id(value));
        *index += 1;
    }

    return (*index != size);
}

LONG_list contains_word(TAD_community com, char* word, int N)
{
    int index = 0;// ( list , ( ( &index , &size ) , word) )
    int i;

    Record y, x = createRecord( create_list(N) , createRecord( createRecord(&index , &N ) , word ) );
    
    x = arrayRev_transversal(com, match, x );

    for(i = index; i< N; i++ )
        set_list((LONG_list) x->fst , i, 0);

    y=x->snd;
    g_free( y->fst );
    g_free( y );
    g_free( x );

    return ((LONG_list) x->fst);
}

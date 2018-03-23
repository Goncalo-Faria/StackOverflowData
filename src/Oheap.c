#include <glib.h>
#include "heap.h"

#define full(x) ((x)->use == (x)->len)
#define quarter(x) (((x)->use * 4) <= (x)->len)

// negative value if a < b ; zero if a = b ; positive value if a > b

typedef struct heap
{
    ENTRY *v;
    unsigned long len;
    unsigned long use;
    unsigned long type;

    freeFunc dataCl;
    Fcompare cmp;

    void *user_data;

} * HEAP;

// Métodos publicos
HEAP create_H(freeFunc in_free, Fcompare ff, void *usr_d);
HEAP create_fixed_H(ENTRY *v, unsigned long n, freeFunc in_free, Fcompare h, void *usr_d);
void destroy_H(HEAP x);
HEAP add_Heap(HEAP x, void *n);
HEAP add_in_Place_H(HEAP x, void *n);
void *rem_Heap(HEAP x);
int empty_H(HEAP x);
unsigned long length_H(HEAP x);

// Métodos privados
static HEAP tabledouble(HEAP x);
static HEAP tablehalv(HEAP x);
static ENTRY *Swap(ENTRY *v, unsigned long i, unsigned long j);
static ENTRY *BubleUp(ENTRY *v, unsigned long i, Fcompare h, void *user_data);
static ENTRY *BubleDown(ENTRY *v, unsigned long i, unsigned long N, Fcompare h, void *user_data);

int empty_H(HEAP x)
{
    return (x->use == 0);
}

unsigned long length_H(HEAP x)
{
    return x->use;
}

HEAP create_H(freeFunc in_free, Fcompare ff, void *usr_d)
{
    HEAP x = (HEAP)g_malloc(sizeof(struct heap));
    x->use = 0;
    x->v = g_malloc(1 * sizeof(ENTRY));
    x->len = 1;
    x->cmp = ff;
    x->dataCl = in_free;
    x->type = 1;

    x->user_data = usr_d;

    return x;
}

void destroy_H(HEAP x)
{

    freeFunc ff = x->dataCl;

    unsigned long i;
    int r = !(ff == NULL);
    if (x)
    {
        if (x->type)
        {
            for (i = 0; i < x->use; i++)
            {
                if (x->v[i] && r)
                    ff(x->v[i]);
                //free(x->v[i]);
            }
            g_free(x->v);
        }
        g_free(x);
    }
}

HEAP add_Heap(HEAP x, void *n)
{

    if (full(x))
        x = tabledouble(x);
    x->v[x->use++] = n;
    x->v = BubleUp(x->v, x->use - 1, x->cmp, x->user_data);
    return x;
}

void *rem_Heap(HEAP x)
{

    void *n;
    if (quarter(x))
        x = tablehalv(x);

    if (x->use > 0)
    {
        n = x->v[0];
        x->v[0] = NULL;
        x->v = Swap(x->v, 0, --x->use);
        x->v = BubleDown(x->v, 0, x->use, x->cmp, x->user_data);
        return n;
    }
    return NULL;
}

HEAP add_in_Place_H(HEAP x, void *n)
{ // no topo tem o máximo.

    if (x->cmp(x->v[0], n, x->user_data) > 0)
    {

        if (x->dataCl)
            x->dataCl(x->v[0]);

        x->v[0] = n;
        x->v = BubleDown(x->v, 0, x->use, x->cmp, x->user_data);
    }
    else
    {

        if (x->dataCl)
            x->dataCl(n);
    }

    return x;
}

HEAP create_fixed_H(ENTRY *v, unsigned long n, freeFunc in_free, Fcompare h, void *usr_d)
{
    HEAP x = g_malloc(sizeof(struct heap));
    long i;
    x->dataCl = in_free;
    x->len = x->use = n;
    x->cmp = h;
    x->type = 1; // must be erased
    x->user_data = usr_d;

    x->v = g_memdup(v, sizeof(void *) * x->len); // duplicate

    // floyd algo.

    for (i = n / 2; i >= 0; i--)
        v = BubleDown(x->v, i, n, h, x->user_data);

    return x;
}

static HEAP tabledouble(HEAP x)
{

    x->len *= 2;
    x->v = g_realloc(x->v, x->len * sizeof(ENTRY));
    return x;
}

static HEAP tablehalv(HEAP x)
{

    x->len = x->len / 2;
    x->v = g_realloc(x->v, x->len * sizeof(ENTRY));
    return x;
}

static ENTRY *Swap(ENTRY *v, unsigned long i, unsigned long j)
{

    ENTRY t;

    if (i == j)
        return v;
    // t = v[i];
    //
    t = v[i];

    //
    //v[i] = v[ j ];
    //
    v[i] = v[j];

    //
    // v[ j ] = t;
    //
    v[j] = t;

    return v;
}

static ENTRY *BubleUp(ENTRY *v, unsigned long i, Fcompare h, void *user_data)
{

    if (!i)
        return v;

    if (h(v[i], v[pai(i)], user_data) * (-1) < 0)
    { //v[i]->key < v[ pai(i) ]->key)
        v = Swap(v, i, pai(i));
        v = BubleUp(v, pai(i), h, user_data);
    }
    return v;
}

static ENTRY *BubleDown(ENTRY *v, unsigned long i, unsigned long N, Fcompare h, void *user_data)
{

    unsigned long f = esq(i);

    if (f > N - 1 || N < 1)
        return v;

    if (f + 1 < N)
        f = (h(v[f], v[f + 1], user_data) * (-1) < 0) ? f : f + 1; // v[f]->key < v[f+1]->key

    if (h(v[f], v[i], user_data) * (-1) < 0)
    { //  v[f]->key < v[i]->key
        v = Swap(v, f, i);
        v = BubleDown(v, f, N, h, user_data);
    }
    return v;
}
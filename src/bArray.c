#include <bArray.h>
#include <glib.h>

#define full(x) (x->use == x->size)

#define get_start(x, from) find(x, from, -1)
#define get_end(x, from) find(x, from, 1)

typedef void (*freeFunc)(void *);
/*
    Dados.
*/
typedef int (*appFunc)(void *, void *);
/*
    Dados /->userdata 
*/
typedef int (*cmpFunc)(void *, void *, void *);
/*
    Compare function.
*/

typedef struct brray
{

    void **v;
    unsigned long size;
    unsigned long use;
    cmpFunc a;
    freeFunc b;

    void *user_data;

    int ord;

} * bArray;

// Métodos públicos.

bArray init_A(unsigned long n, freeFunc dados, cmpFunc compare, void *user_data);
int add_to_A(bArray x, void *ele);
void destroy_A(bArray x);
void sort_A(bArray x);
void for_each(bArray x, appFunc functor, void *user_data);
void for_each_from_to(bArray x, void *begin, void *end, appFunc functor, void *user_data);

HEAP Generalized_Priority_Queue(bArray ll, unsigned long Qsize, cmpFunc alt_cmp);
HEAP from_to_Priority_Queue(bArray x, void *begin, void *end, unsigned long Qsize, cmpFunc alt_cmp);

// Métodos privados.
static void fmap(bArray ll, unsigned long start, unsigned long n, appFunc functor, void *user_data);
static long find(bArray x, void *from, int flag);
static HEAP GenP(bArray ll, unsigned long start, unsigned long Qsize, unsigned long num_elem, cmpFunc alt_cmp);

// >>>>><

bArray init_A(unsigned long n, freeFunc dados, cmpFunc compare, void *use)
{
    bArray x = (bArray)g_malloc(sizeof(struct brray));
    x->a = compare;
    x->b = dados;
    x->user_data = use;

    x->v = (void **)g_malloc(sizeof(void *) * n);
    x->size = n;
    x->use = 0;
    x->ord = 0;

    return x;
}

int add_to_A(bArray x, void *ele)
{

    freeFunc ff = x->b;
    if (!full(x))
    {
        x->v[x->use++] = ele;
        return 1;
    }
    if (ff)
        ff(ele);

    return 0;
}

void destroy_A(bArray x)
{
    int i;
    freeFunc ff = x->b;

    for (i = 0; i < x->use; i++)
        if (ff)
            ff(x->v[i]);

    g_free(x->v);
    g_free(x);
}

int static inv(void *a, void *b, void *user_data)
{

    Fcompare ur_data = (Fcompare)user_data;

    return (-1) * ur_data(a, b, NULL);
}

void sort_A(bArray x)
{

    HEAP y = heapify_H(x->v, x->size, inv, (void *)x->a);
    unsigned long num;

    x->v = getDestroy_H(y, &num);

    x->ord = 1;
}

void for_each_from_to(bArray x, void *begin, void *end, appFunc functor, void *user_data)
{
    long s, e;

    if (x->ord)
    {
        s = get_start(x, begin);
        e = get_end(x, end);
        // tem que estar ordenado.

        if (!begin)
            s = 0;
        if (!end)
            e = x->use - 1;

        if (s == -1 || e == -1)
            return;

        fmap(x, (unsigned long)s, (unsigned long)(e - s), functor, user_data);
    }
}

void for_each(bArray x, appFunc functor, void *user_data)
{

    for_each_from_to(x, NULL, NULL, functor, user_data);
}

HEAP from_to_Priority_Queue(bArray x, void *begin, void *end, unsigned long Qsize, cmpFunc alt_cmp)
{

    long s = get_start(x, begin);
    long e = get_end(x, end);

    if (s == -1 || e == -1)
        return NULL;

    return GenP(x, (unsigned long)s, Qsize, (unsigned long)e - s, alt_cmp);
}

HEAP Generalized_Priority_Queue(bArray ll, unsigned long Qsize, cmpFunc alt_cmp)
{

    return (GenP(ll, 0, Qsize, ll->use, alt_cmp));
}

static void fmap(bArray ll, unsigned long start, unsigned long n, appFunc functor, void *user_data)
{

    unsigned long i;
    unsigned long sum = start + n;

    if (start >= ll->use || !ll->ord)
        return;

    if (start + n > ll->use)
        sum = ll->use;

    for (i = start; i < sum; i++)
        functor(ll->v[i], user_data);
}

static long find(bArray x, void *from, int flag)
{
    long inicio, fim, meio;
    long res = 0;
    cmpFunc comp = (cmpFunc)x->a;

    if (!x->size || !x->ord || !from)
        return -1;
    else
    {

        inicio = 0;
        fim = x->use - 1;

        if (comp(x->v[fim], from, x->user_data) && (flag == -1) > 0)
            return -1;

        while (inicio < fim)
        {

            meio = (inicio + fim) / 2;

            if (comp(x->v[meio], from, x->user_data) == 0)
            {
                res = meio;
                break;
            }

            else if (comp(x->v[meio], from, x->user_data) < 0)
            {
                fim = meio - 1;
            }

            else if (comp(x->v[meio], from, x->user_data) > 0)
            {
                inicio = meio + 1;
                // res = fim-1;
            }
        }
    }
    /* caso nao encontre e o elemento mais proximo seja o da posicao 0 return 0;
     * caso nao ecnontre e o elemento mais perto !=0 entao -> -1
     */
    res = meio;
    if (flag == -1)
        while (!(comp(x->v[res], from, x->user_data) > 0) && res > 0)
            res--;
    else
        while (!(comp(x->v[res], from, x->user_data) < 0) && res > 0)
            res++;

    return res;
}

static HEAP GenP(bArray ll, unsigned long start, unsigned long Qsize, unsigned long num_elem, cmpFunc alt_cmp)
{

    HEAP x;
    unsigned long i;
    long r = ll->use - start;
    void **the_v = ll->v;

    if (!alt_cmp)
        alt_cmp = ll->a;

    if (start + Qsize > ll->use)
    { // barco fora
        return NULL;
    }

    the_v = the_v + start;

    if (num_elem >= r)
    {
        num_elem = r;
        x = create_fixed_H(ll->v + start, Qsize, ll->b, alt_cmp, ll->user_data);
    }
    else
    {
        return NULL;
    }

    for (i = Qsize; i < num_elem; i++)
        add_in_Place_H(x, ll->v[i]);

    return x;
}
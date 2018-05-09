#include <bArray.h>
#include <glib.h>
#include <stdlib.h>

//-------------------------------------------------------------------------------------
    // Da autoria de Gonçalo Faria && Guilherme Viveiros.
//-------------------------------------------------------------------------------------
//defines
#define full(x) (x->use == x->size)
#define get_start(x, from, cmp) find(x, from, cmp, -1)
#define get_end(x, from, cmp) find(x, from, cmp, 1)

//Estruturas.
typedef struct brray
{
    void **v;
    unsigned long size;
    unsigned long use;
    freeFunc b;
    int ord;

} * bArray;

// Métodos públicos.
bArray init_A(unsigned long n, freeFunc dados);
bArray add_to_A(bArray x, void *ele);
void destroy_A(bArray x);
void *get_atA(bArray b, unsigned long i);
bArray sort_A(bArray x, int (*cmp)(const void *, const void *));
void *for_each_from_to(bArray x, void *begin, void *end, appFunc functor, cmpFunc alt_cmp, void *user_data);
void *for_each(bArray x, appFunc functor, void *user_data);
void *for_each_rev(bArray x, filterFunc functor, void *user_data);
HEAP from_to_Priority_Queue(bArray x, void *begin, void *end, unsigned long Qsize, cmpFunc q_cmp, cmpFunc ord, filterFunc functor, void *user_data);
HEAP Generalized_Priority_Queue(bArray ll, unsigned long Qsize, cmpFunc q_cmp, filterFunc functor, void *user_data);

// Privados
static void *fmap(bArray ll, unsigned long start, unsigned long n, appFunc functor, void *user_data);
static long find(bArray x, void *from, cmpFunc comp, int flag);
static HEAP GenP(bArray ll, unsigned long start, unsigned long Qsize, unsigned long num_elem, cmpFunc alt_cmp, filterFunc functor, void *user_data);

//-------------------------------------------------------------------------------------

static void *fmap(bArray ll, unsigned long start, unsigned long n, appFunc functor, void *user_data)
{

    unsigned long i;
    unsigned long sum = start + n;

    if (start >= ll->use || !ll->ord)
        return user_data;

    if (start + n > ll->use)
        sum = ll->use;

    for (i = start; i < sum; i++)
        functor(ll->v[i], user_data);

    return user_data;
}

static long find(bArray x, void *from, cmpFunc comp, int flag)
{
    long inicio, fim, meio = 0;
    unsigned long res = 0;

    if (!x->size || !x->ord || !from)
        return -1;
    else
    {

        inicio = 0;
        fim = x->use - 1;

        while (inicio < fim)
        {

            meio = (inicio + fim) / 2;

            if (comp(x->v[meio], from, NULL) == 0)
            {
                res = meio;
                break;
            }

            else if (comp(x->v[meio], from, NULL) < 0)
            {
                fim = meio - 1;
            }

            else if (comp(x->v[meio], from, NULL) > 0)
            {
                inicio = meio + 1;
                // res = fim-1;
            }
        }
    }
    /* caso nao encontre e o elemento mais proximo seja o da posicao 0 return 0;
       caso nao ecnontre e o elemento mais perto !=0 entao -> -1
     */
    res = (unsigned long)meio;

    if (flag == -1)
    {
        while ( !comp(x->v[res], from, NULL) && res > 0)
            res--;

        if( comp(x->v[res], from, NULL) )
            res++;
    }
    if( flag == 1)
    {
        while ( !comp(x->v[res], from, NULL) && res < (x->use-1) )
            res++;

        if( comp(x->v[res], from, NULL) )
            res--;
    }
    return res;
}

static HEAP GenP(bArray ll, unsigned long start, unsigned long Qsize, unsigned long num_elem, cmpFunc alt_cmp, filterFunc functor, void *user_data)
{

    HEAP x;
    unsigned long i;
    long r = ll->use - start;
    ENTRY *the_v = ll->v;

    if (!alt_cmp)
        return NULL;

    if (start + Qsize > ll->use || Qsize <= 0)
    { // barco fora
        return NULL;
    }

    the_v = the_v + start;

    if ((long)num_elem >= r) // os que quero sao maior que os disponiveis.
        num_elem = (unsigned long)r;

    x = create_fixed_H(the_v, Qsize, NULL, alt_cmp, NULL);

    for (i = Qsize; i < num_elem; i++)
        if (functor(the_v[i], user_data))
            x = add_in_Place_H(x, the_v[i]);

    return x;
}

//-------------------------------------------------------------------------------------

int is_full(bArray x)
{
    return full(x);
}

unsigned long length_A(bArray x)
{
    return x->use;
}

void *get_atA(bArray b, unsigned long i)
{

    if (i < b->use)
    {
        return b->v[i];
    }

    return NULL;
}

bArray init_A(unsigned long n, freeFunc dados)
{
    bArray x = (bArray)g_malloc(sizeof(struct brray));
    x->b = dados;

    x->v = (void **)g_malloc(sizeof(void *) * n);
    x->size = n;
    x->use = 0;
    x->ord = 0;

    return x;
}

bArray add_to_A(bArray x, void *ele)
{

    freeFunc ff = x->b;
    x->ord = 0;
    if (!full(x))
    {
        x->v[x->use++] = ele;
        return x;
    }
    if (ff)
        ff(ele);

    return x;
}

void destroy_A(bArray x)
{
    unsigned long i;
    freeFunc ff = x->b;

    for (i = 0; i < x->use; i++)
        if (ff)
            ff(x->v[i]);

    g_free(x->v);
    g_free(x);
}

bArray sort_A(bArray x, int (*cmp)(const void *, const void *))
{

    qsort(x->v, x->use, sizeof(void **), cmp);
    x->ord = 1;
    return x;
}

void *for_each_from_to(bArray x, void *begin, void *end, appFunc functor, Fcompare alt_cmp, void *user_data)
{
    long s, e;

    if (x->ord)
    {
        // tem que estar ordenado.

        if (!begin)
            s = 0;
        else
            s = get_start(x, begin, alt_cmp);

        if (!end)
            e = x->use - 1;
        else
            e = get_end(x, end, alt_cmp);

        if (s == -1 || e == -1)
            return x;

        return fmap(x, (unsigned long)s, (unsigned long)(e - s), functor, user_data);
    }
    return x;
}

void *for_each(bArray x, appFunc functor, void *user_data)
{

    return for_each_from_to(x, NULL, NULL, functor, NULL, user_data);
}

void *for_each_rev(bArray x, filterFunc functor, void *user_data)
{

    long i = x->use - 1;
    while ((i >= 0) && functor(x->v[i], user_data))
        i--;
    return user_data;
}

HEAP from_to_Priority_Queue(bArray x, void *begin, void *end, unsigned long Qsize, cmpFunc q_cmp, cmpFunc ord, filterFunc functor, void *user_data)
{
    long s, e;
    if (!x->ord)
        return NULL;

    if (begin)
        s = get_start(x, begin, ord);
    else
        s = 0;

    if (end)
        e = get_end(x, end, ord);
    else
        e = x->use - 1;

    if (s == -1 || e == -1)
        return NULL;

    return GenP(x, (unsigned long)s, Qsize, (unsigned long)e - s, q_cmp, functor, user_data);
}

HEAP Generalized_Priority_Queue(bArray ll, unsigned long Qsize, cmpFunc q_cmp, filterFunc functor, void *user_data)
{
    return GenP(ll, 0, Qsize, ll->use, q_cmp, functor, user_data);
}

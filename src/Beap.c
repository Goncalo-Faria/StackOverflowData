/*
    An implementation based on the paper ..

    Min-Max Heaps and
    Generalized Priority Queue

    by 
    M. D. ATKINSON, J.-R. SACK, N. SANTORO, and T. STROTHOTT
    
    1986
*/

#include <glib.h>
#include "heap.h"
#include <math.h>

#include <stdio.h>

#define nivel(i) (log2((double)(i + 1)))
#define full(x) ((x)->use == (x)->len)

typedef void (*freeFunc)(void *);
typedef void *ENTRY;
typedef int (*Fcompare)(void *, void *, void *);

typedef struct beap
{

    ENTRY *v;
    unsigned long len;
    unsigned long use;

    freeFunc dataCl;
    Fcompare cmp;

    void *user_data;

} * BEAP;

// Métodos privados.

static void *findmax(BEAP x, int *i)
{
    int f = 1;

    if (!x->use)
        return NULL;

    if (f > x->use - 1) // não têm filhos.
        return x->v[0];

    if (f + 1 < x->use)
    {                                          // tem filho direita.
        f = x->v[f] > x->v[f + 1] ? f : f + 1; // f tem o valor do menor filho.
    }
    *i = f;

    return x->v[f];
}

static void Swap(ENTRY *v, unsigned long i, unsigned long j)
{

    ENTRY t;

    if (i == j)
        return;
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
}

static unsigned long minorS(ENTRY *v, unsigned long p, unsigned long N, Fcompare h, void *user_data)
{

    unsigned long f = esq(p);

    //printf("g.. %ld  %ld \n",p,N);

    if (f > N - 1) // não têm filhos.
        return p;

    if (f + 1 < N)
    {                                                       // tem filho direita.
        f = (h(v[f], v[f + 1], user_data) < 0) ? f : f + 1; // f tem o valor do menor filho.
    }

    return ((h(v[f], v[p], user_data) < 0) ? f : p);
}

static unsigned long majorS(ENTRY *v, unsigned long p, unsigned long N, Fcompare h, void *user_data)
{

    unsigned long f = esq(p);
    //printf("g.. %ld  %ld \n",p,N);

    if (f > N - 1) // não têm filhos.
        return p;

    if (f + 1 < N)
    {                                                       // tem filho direita.
        f = (h(v[f], v[f + 1], user_data) > 0) ? f : f + 1; // f tem o valor do menor filho.
    }

    return ((h(v[f], v[p], user_data) > 0) ? f : p);
}

static void TrickleDownMin(ENTRY *v, unsigned long i, unsigned long N, Fcompare h, void *user_data)
{

    unsigned long f = esq(i);
    unsigned long minorLeft, minorRight;

    //printf("min... %ld  %ld \n",i,N);

    if (f > N - 1) // não tem filhos.
        return;

    if (f + 1 < N)
    { // tem ambos os filhos.

        minorLeft = minorS(v, f, N, h, user_data);
        minorRight = minorS(v, f + 1, N, h, user_data);

        f = (h(v[minorLeft], v[minorRight], user_data) < 0) ? minorLeft : minorRight;
    }

    if (h(v[f], v[i], user_data) < 0)
    {
        Swap(v, f, i);
        TrickleDownMin(v, f, N, h, user_data);
    }
}

static void TrickleDownMax(ENTRY *v, unsigned long i, unsigned long N, Fcompare h, void *user_data)
{

    unsigned long f = esq(i);
    unsigned long majorLeft, majorRight;

    //printf("max... %ld  %ld \n",i,N);

    if (f > N - 1) // não tem filhos.
        return;

    if (f + 1 < N)
    { // tem ambos os filhos.

        majorLeft = majorS(v, f, N, h, user_data);
        majorRight = majorS(v, f + 1, N, h, user_data);

        f = (h(v[majorLeft], v[majorRight], user_data) > 0) ? majorLeft : majorRight;
    }

    if (h(v[f], v[i], user_data) > 0)
    {
        Swap(v, f, i);
        TrickleDownMax(v, f, N, h, user_data);
    }
}

static void TrickleDown(ENTRY *v, unsigned long i, unsigned long N, Fcompare h, void *user_data)
{

    //printf("3232 %ld  %ld  %d \n",i,N, (((int)nivel(i))%2) );
    if (N)
    {

        if ((((int)nivel(i)) % 2)) // calcula o nível.p
            TrickleDownMin(v, i, N, h, user_data);
        else
            TrickleDownMax(v, i, N, h, user_data);
    }
}

///////

static void TrickleUpMin(ENTRY *v, unsigned long i, Fcompare h, void *user_data, unsigned int lvl)
{
    unsigned long j = pai(pai(i));

    if (lvl > 1)
    { // tem avô
        if (h(v[i], v[j], user_data) < 0)
        {
            Swap(v, i, j);
            TrickleUpMin(v, j, h, user_data, lvl - 2);
        }
    }
}

static void TrickleUpMax(ENTRY *v, unsigned long i, Fcompare h, void *user_data, unsigned int lvl)
{
    unsigned long j = pai(pai(i));

    if (lvl > 1)
    { // tem avô
        if (h(v[i], v[j], user_data) > 0)
        {
            Swap(v, i, j);
            TrickleUpMax(v, j, h, user_data, lvl - 2);
        }
    }
}

static void TrickleUp(ENTRY *v, unsigned long i, Fcompare h, void *user_data)
{
    unsigned int lvl = (unsigned int)nivel(i);
    unsigned int r = (pai(i) > -1);

    if (!(lvl % 2))
    { // calcula o nível.

        if (r && (h(v[i], v[pai(i)], user_data) > 0))
        { // v[i]> v[pai(i)]
            Swap(v, i, pai(i));
            TrickleUpMax(v, pai(i), h, user_data, lvl - 1);
        }
        else
        {
            TrickleUpMin(v, i, h, user_data, lvl);
        }
    }
    else
    {

        if (r && (h(v[i], v[pai(i)], user_data) < 0))
        {
            Swap(v, i, pai(i));
            TrickleUpMin(v, pai(i), h, user_data, lvl - 1);
        }
        else
        {
            TrickleUpMax(v, i, h, user_data, lvl);
        }
    }
}
////////

unsigned long length_B(BEAP x)
{
    return x->use;
}

unsigned long Capacity_B(BEAP x)
{
    return x->len;
}

int empty_B(BEAP x)
{
    return (x->use == 0);
}

BEAP create_B(unsigned long N, freeFunc in_free, Fcompare ff, ENTRY *g, void *usr_d)
{
    long i;
    BEAP x = (BEAP)g_malloc(sizeof(struct beap));
    x->v = g_malloc(N * sizeof(ENTRY));
    x->len = N;
    x->use = N;
    x->cmp = ff;
    x->dataCl = in_free;

    x->user_data = usr_d;

    for (i = 0; i < N; i++)
        x->v[i] = g[i];

    //for( i=1 ; i<N ; i++)
    //TrickleUp(x->v, i, x->cmp, x->user_data);

    //for (i= N/2 ; i>=0 ; i-- )
    // TrickleDown( x->v, i, N, x->cmp, x->user_data);

    return x;
}

void destroy_B(BEAP x)
{

    freeFunc ff = x->dataCl;

    long i;
    int r = !(ff == NULL);
    if (x)
    {
        for (i = 0; i < x->use; i++)
        {
            if (x->v[i] && r)
                ff(x->v[i]);
            //free(x->v[i]);
        }
        g_free(x->v);
        g_free(x);
    }
}

void *rem_Beap(BEAP x)
{

    void *n;

    if (x->use > 0)
    {
        n = x->v[0];
        x->v[0] = NULL;
        Swap(x->v, 0, --x->use);
        TrickleDown(x->v, 0, x->use, x->cmp, x->user_data);
        return n;
    }
    return NULL;
}

void addInplace_Beap(BEAP x, void *n)
{

    Fcompare h = x->cmp;
    freeFunc eco = x->dataCl;
    int i;

    //int *a,*b = findmax(x,&i) ;
    //a = n;
    //printf(" max %d ,  adder %d \n", *b,*a);
    //printf("::: %d \n",h(findmax(x,&i) , n, x->user_data) > 0);
    //printf(" ->>> %d \n",i);// r = (i==1) ? 2:1 ;
    if (h(findmax(x, &i), n, x->user_data) > 0)
    { // é maior que o maximo
        if (eco)
            eco(n);
    }
    else
    {

        if (eco)
            eco(x->v[i]);
        //-> n
        x->v[i] = NULL;
        Swap(x->v, i, x->use - 1);
        TrickleDown(x->v, (unsigned long)i, x->use - 1, x->cmp, x->user_data);

        x->v[x->use - 1] = n;

        TrickleUp(x->v, (unsigned long)(x->use - 1), x->cmp, x->user_data);
    }
}

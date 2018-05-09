#include "comondec.h"
#include "Publicacao.h"
#include "Utilizador.h"
#include <glib.h>
#include <date.h>
#include <string.h>

//-------------------------------------------------------------------------------------
    // Da autoria de Gonçalo Faria && Guilherme Viveiros.
//-------------------------------------------------------------------------------------


typedef struct record
{
    void *fst;
    void *snd;
} * Record;

// --------------------------------------------------------------------------------------
    //Este módulo define os comparadores.

Record createRecord(void *fs, void *sn)
{
    Record a = g_malloc(sizeof(struct record));
    a->fst = fs;
    a->snd = sn;
    return a;
}

void *getFst(Record x)
{
    return x->fst;
}

void *getSnd(Record x)
{
    return x->snd;
}

Record setFst(Record x, void *val)
{
    x->fst = val;
    return x;
}

Record setSnd(Record x, void *val)
{
    x->snd = val;
    return x;
}

int yes(void *a, void *b)
{
    return 1;
}

int is_A(void *value, void *user_data)
{
    return (2 == getP_type((Post)value));
}

int is_Q(void *value, void *user_data)
{

    return (1 == getP_type((Post)value));
}

int date_compare(const void *a /*x*/, const void *b /*y*/, void *user_data)
{

    Date x = (Date)a, y = (Date)b;

    if (get_year(x) > get_year(y))
        return 1;
    else if (get_year(x) < get_year(y))
        return -1;
    //-----------------------------------------
    if (get_month(x) > get_month(y))
        return 1;
    else if (get_month(x) < get_month(y))
        return -1;
    //-----------------------------------------
    if (get_day(x) > get_day(y))
        return 1;
    else if (get_day(x) < get_day(y))
        return -1;

    return 0;
}

int int_cmp(void *a, void *b, void *user_data)
{
    int *x = (int *)a;
    int *y = (int *)b;

    return (*y - *x);
}

int long_cmp(void *a, void *b, void *user_data)
{
    long x = (long)*(unsigned long *)a;
    long y = (long)*(unsigned long *)b;
    x = (y - x);

    if (x <= 0)
    {
        return -1;
    }
    else
    {
        if (!x)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

int rep_cmp(void *a, void *b, void *user_data)
{
    int anum, bnum;

    anum = (int)getU_rep((Util)a);
    bnum = (int)getU_rep((Util)b);
    return int_cmp(&anum, &bnum, user_data);
}

int post_compare(void *a, void *b, void *user_data) // não vai ser preciso.
{

    Date x = getP_date_point((Post)a);
    Date y = getP_date_point((Post)b);

    return date_compare(x, y, user_data);
}

int tag_count_cmp(void *a, void *b, void *user_data)
{

    Record x = (Record)a;
    Record y = (Record)b;

    return int_cmp(x->snd, y->snd, user_data);
}

int inv_post_compare(void *a, void *b, void *user_data)
{

    return (-1) * post_compare(a, b, user_data);
}

int np_cmp(void *a, void *b, void *user_data)
{
    Util x = (Util)a;
    Util y = (Util)b;

    int anum, bnum;

    anum = (int)(getU_Q(x) + getU_A(x));
    bnum = (int)(getU_Q(y) + getU_A(y));

    return int_cmp(&anum, &bnum, user_data);
}

void tag_count_free(void *y)
{
    Record x = (Record)y;
    g_free(getSnd(x));
    g_free(getFst(x));
    g_free(x);
}

int votes_cmp(void *a, void *b, void *user_data)
{
    Post x = (Post)a;
    Post y = (Post)b;

    int anum, bnum;

    anum = (int)getP_votes(x);
    bnum = (int)getP_votes(y);

    return int_cmp(&anum, &bnum, user_data);
}

int nAns_cmp(void *a, void *b, void *user_data)
{
    Post x = (Post)a;
    Post y = (Post)b;

    int anum, bnum;

    anum = getP_ansCount(x);
    bnum = getP_ansCount(y);

    return int_cmp(&anum, &bnum, user_data);
}

int post_ord(const void *a, const void *b)
{

    Post an = *(Post *)a;
    Post bn = *(Post *)b;

    return date_compare(getP_date_point(an), getP_date_point(bn), NULL);
}

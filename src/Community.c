#include <glib.h>
#include "Community.h"
#include <date.h>
#include "bArray.h"

typedef struct TCD_community
{
    GHashTable *userById;

    GHashTable *userByName;
    bArray PostArray;
    GHashTable *post;

} * TAD_community;

/*
*/

int date_compare(const void *a /*x*/, const void *b /*y*/, void *user_data)
{

    // user data será sempre null;
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

static int post_src(void *a, void *b, void *garb)
{ // Post, date.
    Post x = (Post)a;

    return date_compare(getP_date_point(x), (Date)b, NULL);
}
static int post_ord(const void *a, const void *b)
{

    Post an = *(Post *)a;
    Post bn = *(Post *)b;

    return (-1) * date_compare(getP_date_point(an), getP_date_point(bn), NULL);
}

void gen_free_date(void *d)
{
    free_date((Date)d);
}

TAD_community init(void)
{

    TAD_community x = g_malloc(sizeof(struct TCD_community));

    x->userById = g_hash_table_new_full(g_int64_hash, g_int64_equal, NULL, destroyUtil);
    x->userByName = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);

    x->post = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, destroyPost);

    x->PostArray = NULL;
    return x;
}

TAD_community clean(TAD_community com)
{

    g_hash_table_destroy(com->userById);
    g_hash_table_destroy(com->userByName);

    g_hash_table_destroy(com->post);

    if (com->PostArray)
        destroy_A(com->PostArray);

    g_free(com);

    return com;
}

int reverseCompare(void *a, void *b, void *fun)
{

    Fcompare the_func = (Fcompare)fun;
    return (-1) * the_func(a, b, NULL);
}

void turnOn_array(TAD_community com, unsigned long n)
{
    com->PostArray = init_A(n, NULL);
}
void insert_array(TAD_community com, Post x)
{
    add_to_A(com->PostArray, (void *)x);
}

void finalize_array(TAD_community com)
{
    sort_A(com->PostArray, post_ord);
}


HEAP array_Priority_Queue(TAD_community com, unsigned long Qsize, Fcompare q_cmp, int (*filter)(void *, void *), void *user_data)
{

    return Generalized_Priority_Queue(com->PostArray, Qsize, q_cmp, filter, user_data);
}

HEAP arraySeg_Priority_Queue(TAD_community com, Date begin, Date end, unsigned long Qsize, Fcompare q_cmp, int (*filter)(void *, void *), void *user_data)
{

    return from_to_Priority_Queue(com->PostArray, begin, end, Qsize, q_cmp, post_src, filter, user_data);
}

void* arraySeg_transversal(TAD_community com, Date begin, Date end, void (*functor)(void *, void *), void *user_data)
{

    for_each_from_to(com->PostArray, begin, end, functor, post_src, user_data);
    return user_data;
}

// USER HASHTABLE;
int userSet_insert_id(TAD_community com, unsigned long *key, Util x)
{

    return g_hash_table_insert(com->userById, (void *)key, (void *)x);
}

int userSet_insert_name(TAD_community com, unsigned char *key, Util x)
{

    return g_hash_table_insert(com->userByName, (void *)key, (void *)x);
}

void* userSet_id_transversal(TAD_community com, void (*f)(void *, void *, void *), void *x)
{

    g_hash_table_foreach(com->userById, f, x);
    return x;
}

Util userSet_id_lookup(TAD_community com, unsigned long num)
{

    return (Util)g_hash_table_lookup(com->userById, &num);
}

Util userSet_name_lookup(TAD_community com, unsigned char *name)
{

    return (Util)g_hash_table_lookup(com->userByName, name);
}

unsigned int userSet_size(TAD_community com)
{

    return g_hash_table_size(com->userById);
}

// POST HASHTABLE
int postSet_insert(TAD_community com, unsigned int *key, Post x)
{

    return g_hash_table_insert(com->post, (void *)key, (void *)x);
}

Post postSet_lookup(TAD_community com, unsigned int num)
{

    return (Post)g_hash_table_lookup(com->post, &num);
}

void* postSet_transversal(TAD_community com, void (*f)(void *, void *, void *), void *x)
{

    g_hash_table_foreach(com->post, f, x);
    return x;
}

unsigned int postSet_size(TAD_community com)
{

    return g_hash_table_size(com->post);
}

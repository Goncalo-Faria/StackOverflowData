#include <glib.h>
#include "Community.h"
#include <date.h>
#include "bArray.h"
#include "comondec.h"
#include <string.h>

//-------------------------------------------------------------------------------------
// Da autoria de Gonçalo Faria && Guilherme Viveiros.
//-------------------------------------------------------------------------------------

//Estruturas
typedef struct TCD_community
{
    GHashTable *userById;
    bArray PostArray;
    GHashTable *post;
    GHashTable *tagconv;
    int ac;

} * TAD_community;

//Métodos publicos.
TAD_community init(void);
TAD_community clean(TAD_community com);
TAD_community activate(TAD_community com);
TAD_community turnOn_array(TAD_community com, unsigned long n);
TAD_community finalize_array(TAD_community com);
TAD_community assign_tag(TAD_community com, char *key, unsigned int code);
TAD_community userSet_insert_id(TAD_community com, unsigned long *key, Util x);
TAD_community postSet_insert(TAD_community com, unsigned long *key, Post x);
TAD_community insert_array(TAD_community com, Post x);
Util userSet_id_lookup(TAD_community com, unsigned long num);
Post postSet_lookup(TAD_community com, unsigned long num);
unsigned int userSet_size(TAD_community com);
unsigned int postSet_size(TAD_community com);
int is_ON(TAD_community com);
unsigned int code_tag(TAD_community com, char *word);
int contains_tag(TAD_community com, char *word);
void *arraySeg_transversal(TAD_community com, Date begin, Date end, void (*functor)(void *, void *), void *user_data);
void *arrayRev_transversal(TAD_community com, int (*functor)(void *, void *), void *user_data);
void *postSet_transversal(TAD_community com, void (*f)(void *, void *, void *), void *x);
void *userSet_id_transversal(TAD_community com, void (*f)(void *, void *, void *), void *x);
HEAP array_Priority_Queue(TAD_community com, unsigned long Qsize, Fcompare q_cmp, int (*filter)(void *, void *), void *user_data);
HEAP arraySeg_Priority_Queue(TAD_community com, Date begin, Date end, unsigned long Qsize, Fcompare q_cmp, int (*filter)(void *, void *), void *user_data);

//Métodos privados.
static int post_src(void *a, void *b, void *garb);

//-------------------------------------------------------------------------------------

static int post_src(void *a, void *b, void *garb)
{ // Post, date.
    Post x = (Post)a;

    return (-1) * date_compare(getP_date_point(x), (Date)b, NULL);
}

//-------------------------------------------------------------------------------------

TAD_community init(void)
{

    TAD_community x = g_malloc(sizeof(struct TCD_community));

    x->userById = g_hash_table_new_full(g_int64_hash, g_int64_equal, NULL, destroyUtil);

    x->post = g_hash_table_new_full(g_int64_hash, g_int64_equal, NULL, destroyPost);

    x->tagconv = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

    x->PostArray = NULL;
    x->ac = 0;

    return x;
}

TAD_community clean(TAD_community com)
{
    g_hash_table_destroy(com->userById);

    g_hash_table_destroy(com->post);

    if (com->PostArray)
        destroy_A(com->PostArray);

    g_hash_table_destroy(com->tagconv);

    g_free(com);

    return NULL;
}

int is_ON(TAD_community com)
{

    if (com)
        return com->ac;
    else
        return 0;
}

unsigned int tagSet_size(TAD_community com)
{
    return (unsigned int)g_hash_table_size(com->tagconv);
}

int contains_tag(TAD_community com, char *word)
{
    return g_hash_table_contains(com->tagconv, word);
}

unsigned int code_tag(TAD_community com, char *word)
{
    unsigned int *x = (unsigned int *)g_hash_table_lookup(com->tagconv, word);

    if (x)
        return *x;
    else
        return 0;
}

TAD_community assign_tag(TAD_community com, char *key, unsigned int code)
{

    unsigned int *value = g_malloc(sizeof(unsigned int));
    *value = code;
    g_hash_table_insert(com->tagconv, g_memdup(key, sizeof(char) * (strlen(key) + 1)), value);
    return com;
}

TAD_community activate(TAD_community com)
{

    com->ac = 1;
    return com;
}

TAD_community turnOn_array(TAD_community com, unsigned long n)
{
    com->PostArray = init_A(n, NULL);
    return com;
}
TAD_community insert_array(TAD_community com, Post x)
{
    com->PostArray = add_to_A(com->PostArray, (void *)x);
    return com;
}

TAD_community finalize_array(TAD_community com)
{
    com->PostArray = sort_A(com->PostArray, post_ord);
    return com;
}

HEAP array_Priority_Queue(TAD_community com, unsigned long Qsize, Fcompare q_cmp, int (*filter)(void *, void *), void *user_data)
{
    return Generalized_Priority_Queue(com->PostArray, Qsize, q_cmp, filter, user_data);
}

HEAP arraySeg_Priority_Queue(TAD_community com, Date begin, Date end, unsigned long Qsize, Fcompare q_cmp, int (*filter)(void *, void *), void *user_data)
{
    return from_to_Priority_Queue(com->PostArray, begin, end, Qsize, q_cmp, post_src, filter, user_data);
}

void *arraySeg_transversal(TAD_community com, Date begin, Date end, void (*functor)(void *, void *), void *user_data)
{
    return for_each_from_to(com->PostArray, begin, end, functor, post_src, user_data);
}

void *arrayRev_transversal(TAD_community com, int (*functor)(void *, void *), void *user_data)
{
    return for_each_rev(com->PostArray, functor, user_data);
}

// USER HASHTABLE;
TAD_community userSet_insert_id(TAD_community com, unsigned long *key, Util x)
{

    g_hash_table_insert(com->userById, (void *)key, (void *)x);
    return com;
}

void *userSet_id_transversal(TAD_community com, void (*f)(void *, void *, void *), void *x)
{
    g_hash_table_foreach(com->userById, f, x);

    return x;
}

Util userSet_id_lookup(TAD_community com, unsigned long num)
{
    return (Util)g_hash_table_lookup(com->userById, &num);
}

unsigned int userSet_size(TAD_community com)
{
    return g_hash_table_size(com->userById);
}

// POST HASHTABLE
TAD_community postSet_insert(TAD_community com, unsigned long *key, Post x)
{
    g_hash_table_insert(com->post, (void *)key, (void *)x);
    return com;
}

Post postSet_lookup(TAD_community com, unsigned long num)
{
    return (Post)g_hash_table_lookup(com->post, &num);
}

void *postSet_transversal(TAD_community com, void (*f)(void *, void *, void *), void *x)
{
    g_hash_table_foreach(com->post, f, x);
    return x;
}

unsigned int postSet_size(TAD_community com)
{
    return g_hash_table_size(com->post);
}

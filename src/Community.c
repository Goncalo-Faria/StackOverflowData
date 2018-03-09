#include <glib.h>
#include <Community.h>
#include <date.h>

typedef struct TCD_community{
    GHashTable* user;
    GHashTable* post;
    GTree * treeP;
} * TAD_community;

/*
*/

int date_compare ( const void* a /*x*/, const void* b /*y*/,void* user_data){

    // user data será sempre null;
    Date x = (Date)a , y = (Date)b;

    if (get_year(x) > get_year(y) )
        return -1;
    else if( get_year(x) < get_year(y) )
        return 1 ;
    //-----------------------------------------
    if( get_month(x) > get_month(y) )
        return -1;
    else if( get_month(x) < get_month(y) )
        return 1;
    //-----------------------------------------
    if( get_day(x) > get_day(y) )
        return -1;
    else if( get_day(x) < get_day(y) )
        return 1;

    return 0;

}

void gen_free_date(void* d) {
    free_date((Date)d);
}


TAD_community init(void){

    TAD_community x = g_malloc(sizeof(struct TCD_community));

    x->user  = g_hash_table_new_full(g_int64_hash ,  g_int64_equal, g_free , destroyUtil);
    x->post  = g_hash_table_new_full(g_int_hash,  g_int_equal, g_free , destroyPost);

    x->treeP = g_tree_new_full(date_compare, NULL  , NULL , NULL );
    return x;
}

TAD_community clean(TAD_community com){

    g_hash_table_destroy(com->user);
    g_hash_table_destroy(com->post);
    g_tree_destroy(com->treeP);

    return com;
}


// USER HASHTABLE;
int userSet_insert(TAD_community com, unsigned long * key, Util x ){
   
    return g_hash_table_insert(com->user , (void*) key, (void*) x );
}

void userSet_transversal( TAD_community com, void (*f)(void*, void*, void*) ,void* x ){
    
    g_hash_table_foreach( com->user, f , x );
}

Util userSet_lookup( TAD_community com, unsigned long num ){

    return (Util)g_hash_table_lookup(com->user , &num);
}
unsigned int userSet_size(TAD_community com){

    return g_hash_table_size(com->user);
}

// POST HASHTABLE
int postSet_insert(TAD_community com, unsigned int * key, Post x ){
   
    return g_hash_table_insert(com->post , (void*) key, (void*) x );
}

Post postSet_lookup( TAD_community com, unsigned int num ){

    return (Post)g_hash_table_lookup(com->post , &num);
}

void postSet_transversal( TAD_community com, void (*f)(void*, void*, void*) ,void* x ){
    
    g_hash_table_foreach( com->post, f , x );
}

unsigned int postSet_size(TAD_community com){

    return g_hash_table_size(com->post);

}
// POST BALANCED TREE;

void postTree_insert(TAD_community com, Date key, Post x){

    return g_tree_insert(com->treeP, (void*)key , (void*)x );
}

void postTree_transversal( TAD_community com, int (*f)(void*, void*, void*) ,void* x){ // eliminar

    g_tree_foreach (com->treeP ,  f   , x );
}
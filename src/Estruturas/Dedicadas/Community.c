#include <glib.h>
#include <Community.c>

typedef struct TCD_community{
    GHashTable* user;
    GHashTable* post;
    GTree * treeP;
} * TAD_community;

TAD_community init(void){

    TAD_community x = g_malloc(sizeof(struct TCD_community));

    x->user  = g_hash_table_new_full(g_int64_hash ,  g_int64_equal, g_free , destroyUtil);
    x->post  = g_hash_table_new_full(g_int_hash,  g_int_equal, g_free , destroyPost);

    x->treeP = g_tree_new_full(date_compare, NULL  , free_date , NULL );
    return x;
}

TAD_community clean(TAD_community com){

    g_hash_table_destroy(com->user);
    g_hash_table_destroy(com->post);
    g_tree_destroy(com->treeP);

    return com;
}

unsigned int postSet_size(TAD_community com){

    return g_hash_table_size(com->post);
}


unsigned int userSet_size(TAD_community com){

    return g_hash_table_size(com->user);
}

Util userSet_lookup( TAD_community com, unsigned long num ){

    return (Util)g_hash_table_lookup(com->user , &num);
}

Post postSet_lookup( TAD_community com, unsigned int num ){

    return (Post)g_hash_table_lookup(com->post , &num);
}

void userSet_transversal( TAD_community com, void (*f)(void*, void*, void*) ,void* x ){
    
    g_hash_table_foreach( com->user, f , x );
}

void postSet_transversal( TAD_community com, void (*f)(void*, void*, void*) ,void* x ){
    
    g_hash_table_foreach( com->post, f , x );
}


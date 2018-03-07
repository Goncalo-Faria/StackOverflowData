#include "interface.h"
#include "Bloco.h"
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "Community.h"

// Métodos publicos.
STR_pair info_from_post(TAD_community com, int id);
LONG_list top_most_active(TAD_community com, int N);


// Métodos privados.
static void f (void* key, void* value, void* user_data);




STR_pair info_from_post(TAD_community com, int id){
    char* str1, *str2;
    Util y = NULL;
    Post x = NULL;
    STR_pair result;

    str1=malloc( sizeof(char)*100 );
    str2=malloc( sizeof(char)*100 );

    x = (Post)g_hash_table_lookup(com->post ,&id);
    strcpy(str1,(char*)x->nome);

    id = x->fundador;

    y = (Util)g_hash_table_lookup(com->user ,&id);
    strcpy(str2,(char*)y->nome);

    result = create_pair(str1,str2);

    free(str1);
    free(str2);

    return result;
}

LONG_list top_most_active(TAD_community com, int N){
    int num;

    HEAP x = limcreate_H(N);
    LONG_list ll = create_list(N);
    g_hash_table_foreach(com->user, f , (void*)x)
    
    //
    for(i=0; i<N;i++){
        c = (Util) rem_Heap( x , &num );
        set_list(ll, i , c->id );
    }
    
    destroy_H(x);
    return ll;

}

static void f (void* key, void* value, void* user_data){
    Util x = (Util)value;
    HEAP y = (HEAP)user_data;
    int  num = x->Q + x->A;
    if( maxQ_H(y) )// está na capacidade
        addR_Heap( y, (-1) * num , value , destroyUtil );
    else 
        add_Heap( y , (-1) * num , value );
}






LONG_pair total_posts(TAD community com, Date begin, Date end){
 
 // ia fazer heap com data_begin
    // heap com data_end

    // somar as 2 datas;

}




USER get_user_info(TAD community com, long id){

    User x  = NULL;
    util y = NULL;

    // preciso que o id seja do tipo int
    y = (Util)g_hash_table_lookup(com->util ,& (int *)id);
    // atraves do ID da me isso

    // create_user (char* short_bio, long* post_history);


   
    x = create_user ( x -> bio , x -> Q) ;
    free(y);

    return x;
}



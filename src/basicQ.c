//#include "interface.h"
#include "Bloco.h"
//#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "Community.h"


// auxiliary structures.
typedef struct contain {
    Date dateB;
    Date dateE;
    long q;
    long a;
}*Contain;


// Métodos publicos.
STR_pair info_from_post(TAD_community com, int id);
LONG_list top_most_active(TAD_community com, int N);


// Métodos privados-->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
static void target_freq (void* key, void* value, void* user_data){
    Util x = (Util)value;
    HEAP y = (HEAP)user_data;
    int  num = x->Q + x->A;

    if( maxQ_H(y) )// está na capacidade
        addR_Heap( y, (-1) * num , value , destroyUtil );
    else 
        add_Heap( y , (-1) * num , value );
}

static void target_int( void* key , void *value , void *datas ) {

    Date x = (Date) key ;
    Contain y = (Contain) datas
    Post p = (Post) value;
    /*
    Se as datas forem iguais e tipo for 1 (quest) aumenta as quest e vice-versa para as respostas
    compara atraves do data_compare -> data.h
    */

    if ( date_compare ( x , y->dateB , NULL ) <= 0 && date_compare ( x , y->dateE , NULL) >= 0 ) {
        if ( (p->type) == 1) y->q++;
        else y->a++;
    }
}
/*
// REPARAR -> GONCAS
static void target_ans( void *key , void*value , void* hp ){

    Heap heap = (Heap) hp;

    Contain data = (Contain) key;

    Post post = (Post) value;

    // falta implementar
    int num = p -> score ;
    if ( data_compare ( Contain -> dateB ) <= 0 && data_compare ( Contain -> dateE ) >= 0 && post -> type == 1 ) {
     if ( maxQ_H (heap) )// se está na capacidade
            addR_Heap( data , - 1 * (num)  , post  , destroyPost );
        else 
            add_Heap( data , (-1) * num , post );

}
*/

//->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// -- 1 FEITO
STR_pair info_from_post(TAD_community com, int id){
    char* str1, *str2;
    Util y = NULL;
    Post x = NULL;
    STR_pair result;
    unsigned long userid;

    str1=g_malloc( sizeof(char)*100 );
    str2=g_malloc( sizeof(char)*100 );

    x = (Post)g_hash_table_lookup(com->post ,&id);
    strcpy(str1,(char*)x->nome);

    userid = x->fundador;

    y = (Util)g_hash_table_lookup(com->user ,&userid);
    strcpy(str2,(char*)y->nome);

    result = create_pair(str1,str2);

    free(str1);
    free(str2);

    return result;
}

// --2 FEITO
LONG_list top_most_active(TAD_community com, int N){
    int num;

    HEAP x = limcreate_H(N);
    LONG_list ll = create_list(N);
    g_hash_table_foreach( com->user, f , (void*)x)
    
    //
    for(i=0; i<N;i++){
        c = (Util) rem_Heap( x , &num );
        set_list(ll, i , c->id );
    }
    
    destroy_H(x);
    return ll;

}




// recebe uma avl tree e retira de la as datas , para um su-array defenido no glib
// estou a assumir que recebo uma AVL;

// --3 FEITO
LONG_pair total_posts(TAD community com, Date begin, Date end) {

    Contain x = g_malloc (sizeof (struct contain));
    x->dateB = begin;
    x->dateE = end; 

    // nao esta defenido por incompetencia (LONG_PAIR) xD !!!!!!!!!!!!!!!!!!!!!!!!!!!!
    x->q=0;
    x->a=0;

    g_tree_foreach (com->treeP ,  g  , (void*)x) ;

    LONG_pair res = create_pairr ( x->q , x->a  ) ;
    
    free(x);

    return res;
}

// --4 precisamos da tag
LONG_list questions_with_tag(TAD community com, char* tag, Date begin, Date end) {


}


// --5 ESTA POR ACABAR
USER get_user_info(TAD community com, long id){

USER create_user(char* short_bio, long* post_history);

    Heap x = limcreate_H ( )
    User x  = NULL;
    util y = NULL;

    y = (Util)g_hash_table_lookup(com->util ,id);

    // create_user (char* short_bio, long* post_history);
    x = create_user ( x -> bio , x -> Q) ;
    g_free(y);

    return x;
}

 
// --6 FEITA
LONG_list most_voted_answers(TAD community com, int N, Date begin, Date end){
     int num;
     LONG_list x = create_list(N);

     Heap h = limcreate_H (N);
     g_tree_foreach (com->treeP , n , (void *)x);

     for (int i=0, i < N ; i++){
        post = (Post) rem_Heap( x , &num );
        set_list(x, i , post);
     }


}

// --7 FALTA ACABAR
LONG_list most_answered_questions(TAD community com, int N, Date begin, Date end){

    



}







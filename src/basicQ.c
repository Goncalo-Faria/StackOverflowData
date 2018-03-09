#include "Bloco.h"
//#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include "heap.h"
#include "Community.h"
#include "interface.h"


// auxiliary structures.
typedef struct contain {
    Date dateB;
    Date dateE;
    long q;
    long a;
    void* spec;
}*Container;


// Métodos publicos.
STR_pair info_from_post(TAD_community com, int id);//#1
LONG_list top_most_active(TAD_community com, int N);//#2
LONG_pair total_posts(TAD_community com, Date begin, Date end);//#3
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end);//#6



// Métodos privados-->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
static void heapify (void* key, void* value, void* user_data){
    Util x = (Util)value;
    HEAP y = (HEAP)user_data;
    int  num = getU_Q( x ) + getU_A( x );

    if( maxQ_H(y) )// está na capacidade
        addR_Heap( y, (-1) * num , key );
    else 
        add_Heap( y , (-1) * num , key );
}

static int count ( void* key , void *value , void *user_data ) {

    Date x = (Date) key ;
    Container box = (Container) user_data;
    LONG_pair k = (LONG_pair)box->spec; 
    Post p = (Post) value;
    /*
    Se as datas forem iguais e tipo for 1 (quest) aumenta as quest e vice-versa para as respostas
    compara atraves do data_compare -> data.h
    */

    if ( date_compare ( x , box->dateB , NULL ) <= 0 && date_compare ( x , box->dateE , NULL) >= 0 ) {
        if ( getP_type( p )  == 1) inc_fstL(k);// é Questão.
        else inc_sndL(k);// não é Questão.
    }

    // The tree is traversed in sorted order.
    if ( date_compare ( x , box->dateE , NULL )<0 )
        return 1;
    return 0;
}

// REPARAR -> GONCAS
static int find_ans ( void *key , void*value , void* user_data ){

    Container box = (Container) user_data;
    HEAP x = (HEAP)box->spec;
    Post post = (Post)value;
    int num = getP_score(post);


    if ( date_compare ( box->dateB , (Date) key ,NULL) <= 0 && date_compare ( box->dateE, (Date) key,NULL ) >= 0 && getP_type(post) == 2 ){// é resposta.
        if ( maxQ_H (x) )// se está na capacidade
            addR_Heap( x , (-1) * num , post );
        else 
            add_Heap( x , (-1) * num , post  );
        }

    // The tree is traversed in sorted order.
    if ( date_compare ( x , box->dateE , NULL )<0 )
        return 1;
    return 0;

}

static Container createContainer(Date begin, Date end ){ 

    Container x = g_malloc (sizeof (struct contain));
    x->dateB = begin;
    x->dateE = end; 
    x->spec= NULL;
    return x;

}

//->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// -- 1 FEITO
STR_pair info_from_post(TAD_community com, int id){
    unsigned char* str1, *str2;
    Util y = NULL;
    Post x = NULL;
    STR_pair result;
    unsigned long userid;
    
    x = postSet_lookup(com, id);

    str1 = getP_name(x);
    userid = getP_fund(x);
    
    y = userSet_lookup(com, userid);

    str2 = getU_name(y);
    result = create_pair((char*)str1,(char*)str2);

    g_free(str1);
    g_free(str2);

    return result;
}

// --2 FEITO
LONG_list top_most_active(TAD_community com, int N){
    int num,i;

    HEAP x = limcreate_H(N, NULL);// não elimina conteudo.
    LONG_list ll = create_list(N);
    unsigned long* c;

    userSet_transversal( com, heapify , (void*)x);
    
    //
    for(i=0; i<N;i++){
        c = (unsigned long* ) rem_Heap( x , &num );
        set_list(ll, i , *c );
    }
    
    destroy_H(x);
    return ll;

}

// recebe uma avl tree e retira de la as datas , para um su-array defenido no glib
// estou a assumir que recebo uma AVL;

// --3 FEITO
LONG_pair total_posts(TAD_community com, Date begin, Date end) {

    Container x = createContainer(begin,end);
    x->spec  = (void*)create_pairL(0,0);

    // nao esta defenido por incompetencia (LONG_PAIR) xD !!!!!!!!!!!!!!!!!!!!!!!!!!!!

    postTree_transversal( com ,count, (void*)x );

    LONG_pair res = (LONG_pair) x->spec;
    g_free(x);

    return res;
}

// --4 precisamos da tag
/*
LONG_list questions_with_tag(TAD community com, char* tag, Date begin, Date end) {


}
*/


// --5 ESTA POR ACABAR 

/*
USER get_user_info(TAD community com, long id){

 //USER create_user(char* short_bio, long* post_history);

    Heap x = limcreate_H ( )
    User x  = NULL;
    util y = NULL;

    y = (Util)g_hash_table_lookup(com->util ,id);

    // create_user (char* short_bio, long* post_history);
    x = create_user ( x -> bio , x -> Q) ;
    g_free(y);

    return x;
}
 */
// createContainer

// --6 FEITA
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
    int num, i;
    LONG_list ll; 
    Post newp;
    Container carrier = createContainer(begin,end);
    carrier->spec   = (void*)limcreate_H (N , NULL);

    postTree_transversal( com , find_ans , (void*)carrier );

    ll = create_list(N);

    for ( i=0; i < N ; i++){
        newp = (Post)rem_Heap( (HEAP)carrier->spec , &num );
        set_list(ll , i , getP_id ( newp ) );
    }

    destroy_H(carrier->spec);
    g_free(carrier);

    return ll;
}
/*
// --7 FALTA ACABAR
LONG_list most_answered_questions(TAD community com, int N, Date begin, Date end){

    



}





*/

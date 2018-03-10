//#include "Bloco.h"
//#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include "heap.h"
#include "Community.h"
//#include "interface.h"

#define inc_fst_long(x) set_fst_long( x , 1 + get_fst_long(x) )
#define inc_snd_long(x) set_snd_long( x , 1 + get_snd_long(x) )

// auxiliary structures.
typedef struct contain {
    Date dateB;
    Date dateE;

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
        if ( getP_type( p )  == 1)  inc_fst_long(k);// é Questão.
        else  inc_snd_long(k);// não é Questão.
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

static int more_answer ( void *key , void*value , void* user_data ){

    Container box = (Container) user_data;
    HEAP x = (HEAP)box->spec;
    Post post = (Post)value;
    int num = getP_answers(post);


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
    result = create_str_pair((char*)str1,(char*)str2);

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

    Container x = createContainer(begin,end);//set_snd_long
    x->spec  = (void*)create_long_pair(0,0);

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

/* ACABARRRRRRRRRRRRRRRR
// --5 ESTA POR ACABAR 
USER get_user_info(TAD community com, long id){
    int i=0;
    Heap h =limcreate_H(10);
    User info = g_malloc (sizeof (struct user));
    long *post_history =NULL;
    char *short_bio = NULL;
    Util x = userSet_lookup ( com , id);


    // meu objetivo aqui recebo UM ID  de um USER e atraves disso consigo a sua bacia
    // COMO apenas quero um bio e LONG* HISTORY fasso uma heap com as datas mais antigas e assim sucessivamente
    // Depois so tenho que retirar 10 datas
    // Caso em que nao tenho 10? , devolvo apenas o array com os ID recebidos
    GHashTable *h = get_Bacia(x);


    strcpy (short_bio , x->bio);

    // aqui tennho a minha heap h com as 10 datas mais antigas 
    
    // FAZERRRRRRRRRRRRRRRR

    // verificar se os dados sao == NULL ou nao para saber se o post é do User ou nao


    // começo de 10 pois é para estar ordenado por cronologia inversa
    for (i=10; i > 0 ; i--){
        *post_history = // remove da heap 1 a 1 ... (h , )
        //usar o rem_heap -> remove o elemento que esta no topo da lista
        post_history++;
    }

    destroyUtil(x);
    destroy_H(h);
    info = create_user(short_bio ,post_history);

    return (info);
}
*/

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


// VERIFICAR SE O MORE_ANSWER ESTA CERTOOOOOOOOOOOOOOOOO'O''O'O'O'OO''O'O'O'O'O'O'O'O'O'O'O'O'O'O'O'O'
// VERIFICAR SE O MORE_ANSWER ESTA CERTOOOOOOOOOOOOOOOOO'O''O'O'O'OO''O'O'O'O'O'O'O'O'O'O'O'O'O'O'O'O'
// --7 FALTA ACABAR
LONG_list most_answered_questions(TAD community com, int N, Date begin, Date end){
    int num;
    LONG_list lista = create_list(N);
    Post p = NULL;

    Container carrier = createContainer(begin,end);
    carrier->spec = (void*)limcreate_H (N,NULL);

    postTree_transversals (com , more_answer , (void*) carrier );
    // ja me mete em ordem decrescente
    while(N>0){
        p = (Post)rem_Heap( (HEAP)carrier->spec ,&num);
        set_list(lista, N , getP_id (p))  ;
        N++;
    }
    destroy_H (carrier->spec);
    g_free(carrier);
    destroyPost(p);

    return lista;
}

/*
}

// --8 FALTA ACBABAR
LONG_list contains_word(TAD community com, char* word, int N){
    LONG_list lista = create_list (N);

}


*/

GONCASSSSS :DDDD , poes isto aqui para te irritar xd




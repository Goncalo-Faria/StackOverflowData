#include <glib.h>
#include <string.h>
#include "heap.h"
#include "Community.h"


// Estruturas  privadas
typedef struct record {
    void* fst;
    void* snd;
}*Record;
/////

// Métodos Publicos
USER get_user_info(TAD_community com, long id);//#5


// Métodos Privados.
static Record createRecord(void * fs, void * sn ){
    Record a = g_malloc( sizeof( struct record ) );
    a->fst = fs;
    a->snd = sn;
    return a;
}

static void collect_top10 (void* key, void* value, void* user_data){
    
    unsigned long* parent = (unsigned long*) key;
    unsigned long* child  = (unsigned long*) value;
    Record carrier = (Record)user_data;
    HEAP x = (HEAP)carrier->fst;
    TAD_community com = (TAD_community)carrier->snd;
    unsigned long* used; 
    Post pub;

    if(child){
        // é uma resposta.
        used = child;
    } else {
        // é uma questão.
        used = parent;
    }

    pub = postSet_lookup(com ,*used );

    add_Heap( x , pub ); // mais tempo fica no topo.

}


////////

USER get_user_info(TAD_community com, long id){
    
    int i;
    Post the_post;
    USER send;
    Record carrier;
    HEAP pQ = create_H(NULL , reverseCompare, (void*) post_compare );
    long post_history[10];
    char *short_bio = NULL;
    Util x = userSet_id_lookup( com ,(unsigned long) id);

    if(!x)  return NULL;
    short_bio =(char*) getU_bio(x);

    carrier = createRecord( (void*)pQ, (void*)com );
    // x->bio;
    toBacia_transversal(x , collect_top10 , carrier );

    for( i=0; i<10;i++){// vai do novo para o velho. (cronologia inversa)
        
        if ( ! empty_H(pQ) ){
        
            the_post = (Post )rem_Heap( pQ );
            post_history[i]= (long) getP_id(the_post)  ;

        } else {
            
            post_history[i] = 0;
        
        }

    }

    send = create_user( short_bio , post_history );

    g_free(short_bio);
    g_free(carrier);
    destroy_H(pQ);
    return send;
}
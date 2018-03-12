#include <bArray.h>
#include <glib.h>

#define full(x) (x->use == x->size)

typedef void (*freeFunc)(void*);
/*
    Dados.
*/
typedef void (*appFunc)(void*, void*);
/*
    Dados /->userdata 
*/
typedef void (*cmpFunc)(void*, void*);
/*
    Compare function.
*/


typedef struct brray {

    void* v[];
    unsigned long size;
    unsigned long use;
    cmpFunc a;
    freeFunc b;

    int ord;

}bArray;

// Métodos públicos.

bArray init_A(unsigned long n, freeFunc dados, cmpFunc compare);
void destroy_A( bArray x );
int add_to_A(bArray x, void* ele );
void sort_A( bArray x);
corner_A(bArray x, void* from, void* to, appFunc f );

// Métodos privados.

static long get_start( bArray x ,void* from);
static long get_end( bArray x ,void* to);

// >>>>><

bArray init_A(unsigned long n, freeFunc dados, cmpFunc compare){
    bArray x = (bArray)g_malloc( sizeof(brray) );
    x->a =compare;
    x->b = dados;

    x->v = (void**)g_malloc( sizeof(void*) * n );
    x->size = n;
    x->use  = 0;
    x->ord  = 0;
}

int add_to_A(bArray x , void* ele ){

    if( ! full(x) ){
        x->v[x->use++] = ele;
        return 1;
    }
    return 0;
}

void destroy_A( bArray x){
    int i;
    freeFunc ff = x->b;

    for( i=0 ; i< x->use; i++ )
        if( ff )
            ff( x->v[i] );

    g_free(x->v);
    g_free(x);
}



///  >>>







static void fmap ( void ** x , unsigned long n, appFunc y, void * user_data ){
    
    unsigned int i;

    for( i= 0; i < n ; i++ )
        y(x[i] ,user_data );


}










void subspace_A ( bArray x , appFunc y ,void* begin , void* end , void* user_data){


    s = get_start(x,begin);
    e = get_end(x,end);

    fmap( x->v + s, e - s + 1, y ,user_data); 
}


























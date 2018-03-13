#include <bArray.h>
#include <glib.h>
#include "heap.h"

#define full(x) (x->use == x->size)

typedef void (*freeFunc)(void*);
/*
    Dados.
*/
typedef void (*appFunc)(void*, void*);
/*
    Dados /->userdata 
*/
typedef void (*cmpFunc)(void*, void*,void*);
/*
    Compare function.
*/

static int int_cmp(void* a , void* b,void* c){
    int* x = (int*) a;
    int* y = (int*) b;

    return ( *y - *x );
}


typedef struct brray {

    void* *v;
    unsigned long size;
    unsigned long use;
    cmpFunc a;
    freeFunc b;

    int ord;

}*bArray;

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
    bArray x = (bArray)g_malloc( sizeof(struct brray) );
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

/*
void sort_A( bArray x){
    int a,b;
    void * temp;
    if( !full(x) ) break;
    else {
        for (a = 1; a < x->use; a++){
            for (b = 0; b < x->use; b++) {
                if (x->v[b] > x->v[b+1])
                temp = x->v[b];
                x->v[b] = x[b + 1];
                x[b + 1] = temp;
               }   
        }
    }
}
*/

corner_A(bArray x, void* from, void* to, appFunc f ){

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


static int int_cmp(void* a , void* b , void* user_data){
    int* x = (int*) a;
    int* y = (int*) b;

    return ( *y - *x );
}



void sort_A( bArray x){

    HEAP y = heapify_H(x->v, x->size , x->a, NULL );
    int num;

    x->v = getDestroy_H( y , &num ); 
}

static long get_start( bArray x ,void* from) {
    long inicio,fim,meio;
    long res=0;

    if (!x->size  || !x->ord ) return -1;
    else{
        inicio=0;
        fim = x->use-1;
        
        while (inicio < fim){

            meio = (inicio + fim)/2;
            
            if ( comp (x->v[meio] , from,NULL) == 0) {
                res = meio;
                break;
            }
            
            else if ( comp (x->v[meio] , from,NULL) >0) {
                fim = meio-1;
            }
            
            else if ( comp (x->v[meio] , from,NULL) < 0 ) {
                inicio = meio +1;
                // res = fim-1;
            }
            
            else break;
        }
    }
    /* caso nao encontre e o elemento mais proximo seja o da posicao 0 return 0;
     * caso nao ecnontre e o elemento mais perto !=0 entao -> -1
     */
    if ( comp (v[res] , from ,NULL) != 0 && res ) return res-1;
    return  res;
}
 
static long get_end( bArray x ,void* from) {
    long inicio,fim,meio;
    long res=0;

    if (!x->size  || !x->ord ) return -1;
    else{
        inicio=0;
        fim = x->use-1;
        
        while (inicio < fim){

            meio = (inicio + fim)/2;
            
            if ( comp (x->v[meio] , from , NULL) == 0) {
                res = meio;
                break;
            }
            
            else if ( comp (x->v[meio] , from , NULL) >0) {
                fim = meio-1;
            }
            
            else if ( comp (x->v[meio] , from, NULL) < 0 ) {
                inicio = meio +1;
            }
            
            else break;
        }
    }
    /* caso nao encontre e o elemento mais proximo seja o da posicao 0 return 0;
     * caso nao ecnontre e o elemento mais perto !=0 entao -> -1
     */
    if ( comp (v[res] , from ,NULL) != 0 && res!= x->use ) return res+1;
    return  res;

}













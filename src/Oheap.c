#include <glib.h>

//#include <stdlib.h>
#include "heap.h"
#include <stdio.h>


#define full(x) ( (x)->use == (x)->len )
#define quarter(x) ( ( (x)->use * 4 ) <= (x)->len )


// negative value if a < b ; zero if a = b ; positive value if a > b


typedef struct heap {
    
    ENTRY * v;
    unsigned long len;
    unsigned long use;
    unsigned long type;
    
    freeFunc dataCl;
    Fcompare cmp;

    void* user_data;

} * HEAP;

int empty_H(HEAP x){
    return (x->use == 0);
}

unsigned long length_H(HEAP x){
    return x->use;
}

HEAP create_H( freeFunc in_free , Fcompare ff , void* usr_d ){
    HEAP x = (HEAP)g_malloc( sizeof (struct heap) );
    x->use = 0;
    x->v = g_malloc( 1 * sizeof (ENTRY) );
    x->len = 1;
    x->cmp = ff;
    x->dataCl = in_free;
    x->type = 1;

    x->user_data = usr_d;

    return x ;
}

void destroy_H(HEAP x){

    freeFunc ff = x->dataCl;

    unsigned long i;
    int r = !(ff == NULL);
    if(x){
        if(x->type){
            for(i=0; i < x->use; i++ ){
                if(x->v[i] && r)
                    ff(x->v[i]);
                //free(x->v[i]);
            }
            g_free( x->v );
        }
        g_free( x );
    }

}

static void tabledouble(HEAP x ){

    x->len *= 2;
    x->v = g_realloc(x->v, x->len * sizeof ( ENTRY )  );

}

static void tablehalv(HEAP x){

    x->len = x->len / 2;
    x->v = g_realloc(x->v, x->len * sizeof ( ENTRY )  );

}

static void Swap (ENTRY *v, unsigned long i , unsigned long j){
		
	ENTRY t;
    
    if( i==j )
        return;
	// t = v[i];
    //
    t  = v[i];
   
    //
	//v[i] = v[ j ];
    //
    v[i]= v[j];
   
    //
	// v[ j ] = t;
    //
    v[j]  = t ;

    
} 

static void BubleUp (ENTRY * v , unsigned long i  , Fcompare h, void* user_data){


	if( ! i )
		return;

	if(  h ( v[i] ,v[ pai(i)], user_data)<0 ) {//v[i]->key < v[ pai(i) ]->key)
		Swap(v, i , pai(i) );
		BubleUp(v , pai(i),h , user_data);
	}

}

static void BubleDown (ENTRY * v , unsigned long i, unsigned long N,  Fcompare h, void* user_data ){

	unsigned long f = esq(i); 
	

    if(f > N-1 || N < 1)
		return ;

    if ( f + 1 < N )
		f =  ( h( v[f] , v[f+1],  user_data) < 0 ) ? f : f+1 ;// v[f]->key < v[f+1]->key 

	if( h ( v[f] , v[i], user_data) < 0  ){ //  v[f]->key < v[i]->key
	    Swap (v,f,i ) ;
	    BubleDown (v , f , N , h , user_data) ;	
	}

}


void add_Heap( HEAP x , void* n ){

    if( full(x) ) tabledouble(x);
    x->v[x->use++] = n;
    BubleUp(x->v , x->use-1, x->cmp, x->user_data);
}

void* rem_Heap( HEAP x){

    void *n;
    if ( quarter(x) ) tablehalv(x);
    
    if ( x->use >0 ){
        n    = x->v[0];
        x->v[0]= NULL;
        Swap(x->v,0, --x->use);
        BubleDown(x->v , 0 , x->use, x->cmp, x->user_data);
        return n;
    }
    return NULL;
}

ENTRY* getDestroy_H ( HEAP x , unsigned long * size){
    ENTRY *v = x->v;
    Fcompare h = x->cmp;

    unsigned long i;
    *size = x->use;
    //destroy_H(x);

    
    for(i = 0 ; i<*size ; i++ ){
        Swap( v, 0 , *size - i -1 );
        BubleDown(v , 0 , *size - i -1 ,h , x->user_data);
    } 

    destroy_H(x);
    return v;
}


HEAP heapify_H( ENTRY * v , unsigned long n , Fcompare h, void* usr_d ){
    HEAP x = g_malloc ( sizeof (struct heap ) ) ;
    long i;
    x->dataCl = NULL;
    x->len = x->use = n;
    x->cmp = h;
    x->type = 0;
    x->v = v;
    x->user_data = usr_d;

    // floyd algo.

    for ( i = n/2 ; i >= 0 ; i--)
        BubleDown(x->v, i, n , h , x->user_data);

    return x;
}
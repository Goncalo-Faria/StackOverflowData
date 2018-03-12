//#include <stdlib.h>
#include "heap.h"
#include <glib.h>
#include <stdio.h>

#define full(x) ( (x)->use == (x)->len )
#define quarter(x) ( ( (x)->use * 4 ) <= (x)->len )


typedef void (*freeFunc)(void*);
typedef int (*cmp)(void*,void*);






























typedef struct ent {
    
    int key;
    void * data;

} *ENTRY ;

typedef struct heap {
    
    ENTRY * v;
    int len;
    int use;
    int max;

    freeFunc dataCl;

} * HEAP;

int empty_H(HEAP x){
    return (x->use == 0);
}

int length_H(HEAP x){
    return x->use;
}

int maxQ_H(HEAP x){
    return ( x->use == x->max );
}

HEAP create_H(void (*in_free) (void*) ){
    HEAP x = (HEAP)g_malloc( sizeof (struct heap) );
    x->use=0;
    x->v = g_malloc( 2 * sizeof (ENTRY) );
    x->len = 2;
    x->max = -1;
    x->dataCl = in_free;

    return x;
}

HEAP limcreate_H(int lim, void (*in_free) (void*) ){
    HEAP x = (HEAP)g_malloc( sizeof (struct heap) );
    x->use=0;
    x->v = g_malloc( 2 * sizeof (ENTRY) );
    x->len = 2;
    x->max = lim;
    x->dataCl = in_free;
    
    return x;
}

void destroy_H(HEAP x){

    freeFunc ff = x->dataCl;

    int i,r = !(ff == NULL);
    if(x){
        for(i=0; i < x->use; i++ ){
            if(x->v[i]->data && r)
                ff(x->v[i]->data);
            g_free(x->v[i]);
        }
        g_free( x->v );
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

static void Swap (ENTRY *v, int i , int j){
		
	ENTRY t;
    
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

static void BubleUp (ENTRY * v , int i ){

	if( ! i )
		return;

	if(v[i]->key < v[ pai(i) ]->key){
		Swap(v, i , pai(i) );
		BubleUp(v , pai(i) );
	}

}

static void BubleDown (ENTRY * v , int i, int N ){

	int f = esq(i); 
	if(f > N-1 )
		return ;

    if ( f + 1 < N )
		f = v[f]->key < v[f+1]->key ? f : f+1 ;

	if( v[f]->key < v[i]->key ){
	    Swap (v,f,i ) ;
	    BubleDown (v , f , N ) ;	
	}

}

void addR_Heap( HEAP x, int key , void* n ){
    
    freeFunc ff = x->dataCl;

    add_Heap( x ,  key , n );

    if ( ff )
        ff ( x->v[x->use-1]->data );

    x->v[x->use-1]->data = n;
    x->v[x->use-1]->key  = key;

    BubleUp(x->v , x->use-1 );
}

void add_Heap( HEAP x, int key , void* n ){

    if( full(x) ) tabledouble(x);
    x->v[x->use] = g_malloc( sizeof(struct ent) );
    x->v[x->use]->data = n;
    x->v[x->use++]->key = key;

    BubleUp(x->v , x->use-1 );
}

void* rem_Heap( HEAP x, int *key){

    void *n;

    if ( quarter(x) ) tablehalv(x);

    *key = x->v[0]->key ;
    n    = x->v[0]->data;

    x->v[0]->data = NULL;
    
    Swap(x->v,0, --x->use);
    g_free(x->v[x->use]);

    BubleDown(x->v , 0 , x->use);
    return n;
}

void blueprint ( HEAP x ){
    int i;
    for( i=0; i<x->use; i++){
        printf("> %d -> ",x->v[i]->key);
        
    }
    printf("\n");
} 
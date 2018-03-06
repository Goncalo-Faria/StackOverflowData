#include <stdlib.h>
#include "heap.h"


#define full(x) ( (x)->use == (x)->len )
#define quarter(x) ( ( (x)->use * 4 ) <= (x)->len )


typedef struct ent {
    
    int key;
    size_t fat;
    void * data;

} *ENTRY ;

typedef struct heap {
    
    ENTRY * v;
    int len;
    int use;

} * HEAP;

int length_H(HEAP x){
    return x->use;
}

HEAP create_H(void){
    HEAP x = (HEAP)malloc( sizeof (struct heap) );
    x->use=0;
    x->v = malloc( 2 * sizeof (ENTRY) );
    x->len = 2;
    
    return x;
}

void destroy_H(HEAP x){

    int i;
    if(x){
        for(i=0; i < x->use; i++ ){
            if(x->v[i]->data)
                free(x->v[i]->data);
            free(x->v[i]);
        }
        free( x->v );
        free( x );
    }

}

static void tabledouble(HEAP x ){

    x->len *= 2;
    x->v = realloc(x->v, x->len * sizeof ( ENTRY )  );

}

static void tablehalv(HEAP x){

    x->len = x->len / 2;
    x->v = realloc(x->v, x->len * sizeof ( ENTRY )  );

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

void add_Heap( HEAP x, int key , void* n , size_t fat){

    if( full(x) ) tabledouble(x);
    x->v[x->use] = malloc( sizeof(struct ent) );
    x->v[x->use]->data = n;
    x->v[x->use]->fat = fat;
    x->v[x->use++]->key = key;

    BubleUp(x->v , x->use-1 );
}

void* rem_Heap( HEAP x, int *key, size_t *fat ){

    /*
        the flags are 'u' for use.
                  and 'c' for copy
           
    */

    void *n;

    if ( quarter(x) ) tablehalv(x);

    *key = x->v[0]->key ;
    *fat = x->v[0]->fat ; 
    n    = x->v[0]->data;

    x->v[0]->data = NULL;
    
    Swap(x->v,0, --x->use);
    free(x->v[x->use]);

    BubleDown(x->v , 0 , x->use);
    return n;
}

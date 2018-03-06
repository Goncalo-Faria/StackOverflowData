#include "linkedLL/linkedLL.h"
#include <stdlib.h>
#include <string.h>

#define NOT_INTER(x) ( ( (x) < 0 ) && ( (x) > 1 ) )

#define tbdouble_H(tb) stch(tb, 1)
#define tbhalv_H(tb) stch(tb, 0)

typedef struct tuple {
    char max;
    char min;
}TU;

typedef struct dat {
    unsigned char * word;
    void * info;
    size_t fat;
} *DATA;

typedef struct htable {
    LL * v; 
	TU load;
    unsigned int size;
    unsigned int use; 

} *Htable;


/**
 * HASH FUNCTION.
 * 
 * http://www.cse.yorku.ca/~oz/hash.html
 * 
 * */
static unsigned long hash (unsigned char* word , int N ) {

        unsigned long hash = 5381;
        int c;

        while (c = *word++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash%N;

}


/**/
int add_Ht(Htable tb ,unsigned char * key ,void * info, size_t spc,int*collision );
Htable create_Ht (float loadMax, float loadMin );
void * search_Ht ( Htable tb, unsigned  char* key, size_t * spc );
void destroy_Ht ( Htable tb , int flag );
int remove_Ht(Htable tb,unsigned char*key);

/**/

/**
 * Frees
 */

static int boxDelete (void* op1 , void* x){

    DATA* y=(DATA*) x;
    free(y->word);
    free(y->info);
    return 1;

}

static int wordDelete (void* op1 , void* x){

    DATA* y=(DATA*) x;
    free(y->word);
    return 1;

}


///

static LL* fill_H ( int n ) {
    LL* x = (LL*) malloc( sizeof( LL ) * n );
    int i;

    for(i=0; i<n; i++ )
        x[i] = create_ll();
    
    return x;
}

static void dell_H ( LL * x, int n ) {
    int i;

    for(i=0; i<n; i++ )
        clean_ll( x[i]);

    free(x);
}

Htable create_Ht (float loadMax, float loadMin ){
    Htable hold;

    if( NOT_INTER(loadMax) && NOT_INTER(loadMin) && (loadMin < loadMax) )  
        return NULL;
    
    hold = (Htable)malloc ( sizeof(struct htable) );
    hold->size=1; hold->use=0;

    hold->load.max = (char) (loadMax*100);
    hold->load.min = (char) (loadMin*100); 

    hold->v = fill_H(1);
    return hold;
}

static int stch (Htable tb,int flag) {
    int i,old,j,oldU = tb->use,num,s=0, c;
    size_t fat;
    LL* oldT = tb->v ;
    void* info;
    DATA y;


    old= tb->size;
    tb->use = 0;

    if(flag)
        tb->size= old*2;
    else
        tb->size= old/2;


    tb->v = fill_H( tb->size );

    for(i=0; i<old && oldU; i++) 
        if(! empty_ll( oldT[i] ) ){
            c = length_ll(oldT[i]);
            for( j=0; j<c ;j++){
                info = ind_ll(oldT[i], j, &fat );
                y = (DATA)info;
                add_Ht(tb, y->word , y->info, y->fat, &num);
                s+=num;
                oldU--;
            }
        }

    dell_H(oldT, old);
    return s;
}

static int head_N ( void* a,void *b){
    /*
        auxiliary function.
        f(x)=True;    

        Serve para adicionar à cabeça.
    */
    return -1;
}

int add_Ht(Htable tb , unsigned char * key ,void * info, size_t spc,int*collision ){
    /*
        void* info deverá conter o pedaço e memória final.
    */
    int klen ,ind = hash(key ,tb->size );
    // ---------------------------------
    struct dat g;
    // esta estrutura será copiada-> por completo.
    
    klen = strlen ( key );
    g.word = malloc( sizeof(unsigned char)* (klen+1) );
    strcpy(g.word ,key );
    g.fat  = spc;
    g.info = info;

    *collision = 0;

    if ( (float)tb->use/(float)tb->size >= (float)tb->load.max/100 )
        *collision = tbdouble_H(tb);    

    // os apontadores devem conter o pedaço de memória final.

    if(empty_ll(tb->v[ind] ))
        *collision++;

    ind = add_N(head_N ,tb->v[ind] , &g , sizeof(struct dat) );
    
    if( ind ) // 0 se não adicionou. 
        tb->use++;
    
    return ind;    
}

static int eq (void* op1, void* d ){
    // reflexiva, deterministica, transitiva e simétrica.
    DATA cont = (DATA)d;

    if ( !strcmp( cont->word, (unsigned char*)op1 ))
        return 1;
    
    return 0; 
}

static int eqD (void* op1, void* d ){
    // reflexiva, deterministica, transitiva e simétrica.
    DATA cont = (DATA)d;

    if ( !strcmp( cont->word, (unsigned char*)op1 )){
            boxDelete(NULL, d);
            return 1;
        }
    
    return 0; 
}

void * search_Ht ( Htable tb, unsigned char* key, size_t * spc ){
    unsigned long int ind = hash(key ,tb->size );
    DATA cont;

    if( empty_ll(tb->v[ind] ) )
        return NULL;

    cont = (DATA)search_ll( eq, tb->v[ind], key);

    if( !cont )
        return NULL;

    *spc = cont->fat;
    return cont->info; 
}

int remove_Ht( Htable tb, unsigned char*key){
    unsigned long ind = hash(key ,tb->size );

    if( empty_ll(tb->v[ind] ) )
        return 0;

    ind = rem_N( eqD , tb->v[ind] , key );
    
    if ( (float)tb->use/(float)tb->size <= (float)tb->load.min/100 )
        tbhalv_H(tb);    

    return ind;

}

void destroy_Ht ( Htable tb, int flag  ){
    /*
        Se .info tiver apontadores .. este módulo ná é reponsável por da free deles.

        flag == 1 significa eliminar os dados.
        flag == 0 significa não eliminar os dados.
    */
    unsigned int i;
    //dell_H(tb->v,tb->size);
    if(flag)
        for (i=0; i< tb->size;i++){
            rem_N(  boxDelete , tb->v[i] , NULL );
            free(tb->v[i]);
        }
    else 
        for (i=0; i< tb->size;i++){
            rem_N(  wordDelete , tb->v[i] , NULL );
            free(tb->v[i]);
        }
        

    free(tb);
}
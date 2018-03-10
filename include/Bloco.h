#ifndef bloco_h
#define bloco_h

#include "date.h"

typedef struct utilizador *Util ;
typedef struct post *Post;


#define Q_belongs_hash(user,id) belongs_toBacia(user,id,1)
#define A_belongs_hash(user,id) belongs_toBacia(user,id,2)


// create a new post
void *createPost();
// create a new util
void *createUtil();

//destroy some specify post
void destroyUtil( void* x );
//destroy a specify post
void destroyPost( void* x );

//void setDate ( Post x ,int d,int m ,int a);



// User getters

unsigned int getU_Q(Util x);

unsigned int getU_A(Util x);

unsigned char* getU_name(Util x);
// alloca memoria
unsigned char* getU_bio(Util x);
// alloca memoria


// Post getters
unsigned int getP_id(Post x);

unsigned int * getP_id_point(Post x);

unsigned int getP_parentId(Post x);

unsigned int * getP_parentId_point(Post x);

unsigned long getP_fund(Post x);

unsigned char* getP_name(Post x);

unsigned int getP_score(Post x);

unsigned char getP_type(Post x);

Date getP_date_point( Post x );

Date getP_date( Post x );

//Util setters

void inc_Q(Util x);

void inc_A(Util x);

void setU_name(Util x, const unsigned char* un );

void setU_bio(Util x, const unsigned char* un);

void add_toBacia(Util x, unsigned int * id , void * dados );

int belongs_toBacia ( Util x , unsigned int Parent_id, char flag );

unsigned int * toBacia_lookup( Util x, unsigned int Parent_id );

void bind_toBacia( Util x, Post y );


// Post setters
void setP_id(Post x, unsigned int o );

void setP_parentId(Post x, unsigned int o );

void setP_fund(Post x, long f);

void setP_name(Post x, const unsigned char* un);

void setP_score(Post x, unsigned int s);

void setP_type(Post x, unsigned char t);

void setP_id(Post x, unsigned int o );

void setP_date( Post x , int d, int m , int a );








#endif
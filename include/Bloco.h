#ifndef bloco_h
#define bloco_h


typedef struct utilizador *Util ;
typedef struct post *Post;





// create a new post
void *createPost();
// create a new util
void *createUtil();

//destroy some specify post
void destroyUtil( void* x );
//destroy a specify post
void destroyPost( void* x );

void setDate ( Post x ,int d,int m ,int a);



// User getters
unsigned int getU_Q(Util x);

unsigned int getU_A(Util x);

char* getU_name(Util x);

char* getU_bio(Util x);

// Post getters

unsigned long getP_fund(Post x);

char* getP_name(Post x);

unsigned int getP_Score(Post x);

unsigned char getP_type(Post x);

//Util setters

void incQ(Util x);

void incA(Util x);

void setU_name(Util x, char* un);

void setU_bio(Util x, char* b);

// Post setters

void setP_fund(Post x, long f);

void setP_name(Post x, char* n);

void setP_score(Post x, unsigned int s);

void setP_type(Post x, unsigned char t);








#endif
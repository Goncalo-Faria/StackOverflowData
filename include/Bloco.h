#ifndef bloco_h
#define bloco_h


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

char* getU_name(Util x);

char* getU_bio(Util x);

// Post getters

unsigned long getP_fund(Post x);

char* getP_name(Post x);

unsigned int getP_score(Post x);

unsigned char getP_type(Post x);

//Util setters

void inc_Q(Util x);

void inc_A(Util x);

void setU_name(Util x, const unsigned char* un );

void setU_bio(Util x, const unsigned char* un);

void add_toBacia(Util x, unsigned int * id , void * dados );

int belongs_toBacia ( Util x , unsigned int Parent_id, char flag );

// Post setters

void setP_fund(Post x, long f);

void setP_name(Post x, const unsigned char* un);

void setP_score(Post x, unsigned int s);

void setP_type(Post x, unsigned char t);

void setP_id(Post x, unsigned int o );








#endif
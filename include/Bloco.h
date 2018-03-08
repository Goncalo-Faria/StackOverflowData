#ifndef bloco_h
#define bloco_h

// create a new post
void *createPost();
// create a new util
void *createUtil();

//destroy some specify post
void destroyUtil( void* x );
//destroy a specify post
void destroyPost( void* x );

void setDate ( Post x ,int d,int m ,int a);

//Util Getters
int getQ(Util x);
int getA(Util x);
char* getUN(Util x);
char* getB(Util x);

//Post Getters
int getS(Post x);
char* getN(Post x);
long getF(Post x);
char getT(Post x);

//Util Setters
void setB(Util x, char* b);
void setUN(Util x, char* un);
void setA(Util x, int a);
void setQ(Util x, int q);

//Post Setters
void setT(Post x, char t);
void setS(Post x, int s);
void setN(Post x, char* n);
void setF(Post x, long f)

#endif
#ifndef publicacao_h
#define publicacao_h

#include "date.h"

typedef struct post *Post;

// create a new post
Post createPost();

//destroy a specify post
void destroyPost(void *x);

void *postAnswer_transversal(Post x, void* (*p)(Post, void *), void *a);
//cria o especifico arrays com as tags

// Post getters

unsigned int getP_id(Post x);

unsigned int *getP_id_point(Post x);

unsigned int getP_parentId(Post x);

unsigned int *getP_parentId_point(Post x);

unsigned long getP_fund(Post x);

unsigned char *getP_name(Post x);

unsigned int getP_ansCount(Post x);

unsigned int getP_score(Post x);

unsigned int getP_fav(Post x);

unsigned char getP_type(Post x);

unsigned int getP_nComment(Post x);

unsigned char *getP_name_point(Post x);

Date getP_date_point(Post x);

Date getP_date(Post x);

// Post setters
Post setP_id(Post x, unsigned int o);

Post setP_parentId(Post x, unsigned int o);

Post setP_fund(Post x, long f);

Post setP_ansCount(Post x,unsigned int n);

Post setP_name(Post x, const unsigned char *un);

Post setP_score(Post x, unsigned int s);

Post setP_type(Post x, unsigned char t);

Post setP_id(Post x, unsigned int o);

Post setP_fav(Post x,unsigned int n);

Post setP_date(Post x, int d, int m, int a);

Post setP_nComment(Post x, unsigned int n);

Post setP_addAns(Post x, Post val);

#endif

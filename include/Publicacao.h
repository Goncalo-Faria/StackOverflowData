#ifndef publicacao_h
#define publicacao_h

#include "date.h"

typedef struct post *Post;
// Métodos Publicos.

//cria e devolve um post
Post createPost();

//destroi um especifico post
void destroyPost(void *x);

//guarda as respostas de um post com type->1
void *postAnswer_transversal(Post x, void *(*p)(Post, void *), void *a);
//
void *postTag_transversal(Post x, void (*p)(unsigned int, void *), void *a);

//Post getters ---------------------------------------------------------------

//devolve o Id de um post
unsigned int getP_id(Post x);
//devolve um apontador para o Id de um post
unsigned int *getP_id_point(Post x);
//devolve o ParentId de um post de um post
unsigned int getP_parentId(Post x);
//devolve o apontador para o ParentID de um post
unsigned int *getP_parentId_point(Post x);
//devolve o fundador de um post
unsigned long getP_fund(Post x);
//devolve o nome de um post
unsigned char *getP_name(Post x);
//devolve o apontador para o nome de um post
unsigned char *getP_name_point(Post x);
//
unsigned int getP_ansCount(Post x);
//devolve o score de um post
unsigned int getP_score(Post x);
//devolve o numero de votos de um post
int getP_votes(Post x);
//devolve o tipo de um post
unsigned char getP_type(Post x);
//devolve o numero de respostas de um post
unsigned int getP_nComment(Post x);
//devolve o apontador da data de um post
Date getP_date_point(Post x);
//devolve a data de um post
Date getP_date(Post x);
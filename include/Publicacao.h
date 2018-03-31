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
void *postTag_transversal(Post x, int (*p)( unsigned int, void *), void *a);

//Post setters ---------------------------------------------------------------

Post setP_id(Post x, unsigned long o);
//incrementa uma unidade nos votos do post e devolve o post
Post setP_upVote(Post x);
//decrementa uma unidade nos votos do post e devolve o post
Post setP_downVote(Post x);
//coloca uma determinada data no post e devovle o post
Post setP_date(Post x, int d, int m, int a);
//coloca um determinado numero de comentarios no post e devolve o post
Post setP_nComment(Post x, unsigned int n);
//agrupa as respostas de um Post (perguntas) e devolve o post
Post setP_addAns(Post x, Post val);
//coloca uma determinada tag no post e devolve o post
Post setP_tag(Post x, char *tag, void *set);
//coloca um Id num post e devolve o post
Post setP_id(Post x, unsigned long o);
//coloca um Id do pai no post e devolve o post
Post setP_parentId(Post x, unsigned long o);
//coloca o fundador no post e devolve o post
Post setP_fund(Post x, unsigned long f);
//coloca o numero de respostas no post e devolve o post
Post setP_ansCount(Post x, unsigned int n);
//coloca o nome no post e devolve o post
Post setP_name(Post x, const unsigned char *un);
//coloca o score no post e devolve o post
Post setP_score(Post x, int s);
//coloca o tipo (de um post) no post e devolve o post
Post setP_type(Post x, unsigned char t);
//coloca o id num post e devolve o post

//Post getters ---------------------------------------------------------------

//devolve o Id de um post
unsigned long getP_id(Post x);
//devolve um apontador para o Id de um post
unsigned long *getP_id_point(Post x);
//devolve o ParentId de um post de um post
unsigned long getP_parentId(Post x);
//devolve o apontador para o ParentID de um post
unsigned long *getP_parentId_point(Post x);
//devolve o fundador de um post
unsigned long getP_fund(Post x);
//devolve o nome de um post
unsigned char *getP_name(Post x);
//devolve o apontador para o nome de um post
unsigned char *getP_name_point(Post x);
//
unsigned int getP_ansCount(Post x);
//devolve o score de um post
int getP_score(Post x);
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

#endif
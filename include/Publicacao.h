#ifndef publicacao_h
#define publicacao_h

#include "date.h"

/**
*Estrutura de Publicacoes nomeada Post
*/
typedef struct post *Post;

// Métodos Publicos.

//cria e devolve um post
/**
*Cria uma novo Publicacao
*Devolve  Publicacao
*/
Post createPost();

/**
*Aceita como parametro uma determinada Publicacao
*Destroi a Publicacao e apaga-a da memoria
*/
void destroyPost(void *x);

/**
*Percorre a estrutura de respostas do Post através da funcao e guarda o resultado em data
*Devolve o data
*/
void *postAnswer_transversal(Post x, void *(*p)(Post, void *), void *a);

/**
*Percorre a estrutura de tags do Post através da funcao e guarda o resultado em data
*Devolve o data
*/
void *postTag_transversal(Post x, int (*p)( unsigned int, void *), void *a);


//Post getters ---------------------------------------------------------------

//devolve o Id de um post
/**
*Devolve um long contendo o Id da Publicacao
*/
unsigned long getP_id(Post x);

/**
*Devolve um apontador para o Id da Publicacao
*/
unsigned long *getP_id_point(Post x);

/**
*Devolve um long contendo o ParentId da Publicacao
*/
unsigned long getP_parentId(Post x);

/**
*Devolve um apontador para o ParentId da Publicacao
*/
unsigned long *getP_parentId_point(Post x);

/**
*Devolve um long contendo o fundador da Publicacao
*/
unsigned long getP_fund(Post x);

/**
*Devolve uma string contendo o nome da Publicacao
*/
unsigned char *getP_name(Post x);

/**
*Devolve o apontador para o nome de um post
*/
unsigned char *getP_name_point(Post x);

/**
*Devolve o contador das respostas da Publicacao
*/
unsigned int getP_ansCount(Post x);

/**
*Devolve um int contendo o score da Publicacao
*/
int getP_score(Post x);
//devolve o numero de votos de um post
/**
*Devolve um int contendo os votos da Publicacao
*/
int getP_votes(Post x);

/**
*Devolve um char contendo o tipo da Publicacao (resposta ou pergunta)
*/
unsigned char getP_type(Post x);

/**
*Devolve um int contendo o numero de comentarios
*/
unsigned int getP_nComment(Post x);

/**
*Devolve o apontador da data da Publicacao
*/
Date getP_date_point(Post x);

/**
*Devolve a data da Publicacao
*/
Date getP_date(Post x);

//Post setters ---------------------------------------------------------------

/**
*Atualiza o id de uma Publicacao
*Devolve a Publicacao
*/
Post setP_id(Post x, unsigned long o);

/**
*Atualiza o upVote de uma Publicacao incrementando uma unidade
*Devolve a Publicacao
*/
Post setP_upVote(Post x);


/**
*Atualiza o donwVote de uma Publicacao decrmentando uma unidade
*Devolve a Publicacao
*/
Post setP_downVote(Post x);

/**
*Atualiza a data de uma Publicacao
*Devolve a Publicacao
*/
Post setP_date(Post x, int d, int m, int a);

/**
*Atualiza o numero de comentarios do Post 
*Devolve o Post
*/
Post setP_nComment(Post x, unsigned int n);

/**
*Recebe como argumentos duas Publicacoes ,x e y
*Atualiza a estrutura de respostas do x , as respostas nao se alteram mas o pid passa a ser o y
*Devolve a Publicacao(x)
*/
Post setP_addAns(Post x, Post val);

/**
*Recebe como argumentos uma Publicacao , uma tag e um TAD_Community de tags
*Transforma a tag(se conter varias palavras) em várias tags que de seguida sao transformadas em digitos e colocadas na estrutura de tags da Publicacao
*Devolve a Publicacao
*/
Post setP_tag(Post x, char *tag, void *set);

/**
*Atualiza o Id de uma Publicacao
*Devolve a Publicacao
*/
Post setP_id(Post x, unsigned long o);

/**
*Atualiza o contador / ParentId da Publicacao
*Devolve a Publicacao
*/
Post setP_parentId(Post x, unsigned long o);

/**
*Atualiza o fundador da Publicacao
*Devolve a Publicacao
*/
Post setP_fund(Post x, unsigned long f);

/**
*Atualiza o contador de respostas de uma Publicacao
*Devolve a Publicacao
*/
Post setP_ansCount(Post x, unsigned int n);

/*+
*Atualiza o nome da Publicacao
*Devolve a Publicacao
*/
Post setP_name(Post x, const unsigned char *un);

/**
*Atualiza o score da Publicacao
*Devolve a Publicacao
*/
Post setP_score(Post x, int s);

/**
*Atualiza o tipo da Publicacao (resposta ou pregunta)
*Devolve a Publicacao
*/
Post setP_type(Post x, unsigned char t);

#endif
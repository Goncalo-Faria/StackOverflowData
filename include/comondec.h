#ifndef __COMMON_DEF__
#define __COMMON_DEF__

typedef struct record *Record;

/**
*Cria um Record 
*Devolve um Record
*/
Record createRecord(void *fs, void *sn);

/**
*Devolve o primeiro elemento do Record
*/
void *getFst(Record x);

/**
*Devolve o segundo elemento do Record
*/
void *getSnd(Record x);

/**
*Atualiza o primeiro elemento do Record
*Devolve o Record
*/
Record setFst(Record x, void *val);

/**
 * Destroi o Record
 */
void tag_count_free(void *y);

/**
*Atualiza o segundo elemento do Record
*Devolve o Record
*/
Record setSnd(Record x, void *val);

/**
*Recebe como argumentos um value(Post) e um data
*Devolve um int:
	1 se for resposta
	0 se nao for resposta
*/
int is_A(void *value, void *user_data);

/**
*Recebe como argumentos um value(Post) e um data
*Devolve um int:
	1 se for pergunta
	0 se nao for pergunta
*/
int is_Q(void *value, void *user_data);

/**
*Devolve o inteiro 1
*/
int yes(void *a, void *b);

/**
*Recebe como argumentos uma data a , uma data b e um data
*Funcao compara datas
*Devolve um int
	0 se forem iguais
	1 se a 1 primeira for maior que a segunda
	-1 se a 1 primeira for menor que a segunda
*/
int date_compare(const void *a /*x*/, const void *b /*y*/, void *user_data);

/**
*Devolve um int derivado da comparacao entre dois elementos
*/
int int_cmp(void *a, void *b, void *user_data);

int long_cmp(void *a, void *b, void *user_data);


/**
*Recebe como argumento dois Utilizadores
*Devolve um int derivado da comparacao entre os (respostas+perguntas) Utilizadores
*/
int np_cmp(void *a, void *b, void *user_data);

/**
*Recebe como argumento dois Utilizadores
*Devolve um int derivado da comparacao entre os (reputacao) Utilizadores
*/
int rep_cmp(void *a, void *b, void *user_data);

/**
*Recebe como argumento dois Record
*Devolve um int derivado da comparacao entre os (2 elemento) Record
*/
int tag_count_cmp(void *a, void *b, void *user_data);

/**
*Recebe como argumento duas Publicacoes
*Devolve um int derivado da comparacao entre as (datas) Publicacoes
*/
int post_compare(void *a, void *b, void *user_data); // não vai ser preciso.

/**
*Faz o simetrico da funcao post_compare
*/
int inv_post_compare(void *a, void *b, void *user_data);

/**
*Recebe como argumento duas Publicacoes
*Devolve um int derivado da comparacao entre as (votos) Publicacoes
*/
int votes_cmp(void *a, void *b, void *user_data);

/**
*Recebe como argumento duas Publicacoes
*Devolve um int derivado da comparacao entre as (contador de comentarios) Publicacoes
*/
int nAns_cmp(void *a, void *b, void *user_data);

/**
*Recebe como argumento duas Publicacoes
*Devolve um int derivado da comparacao entre os pointers das datas referente às Publicacoes
*/
int post_ord(const void *a, const void *b);

#endif
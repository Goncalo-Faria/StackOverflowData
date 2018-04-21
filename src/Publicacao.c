#include "Publicacao.h"
#include <string.h>
#include <glib.h>
#include "Community.h"
#include "bArray.h"

//-------------------------------------------------------------------------------------
    // Da autoria de Gonçalo Faria && Guilherme Viveiros.
//-------------------------------------------------------------------------------------

// Estruturas.

typedef struct post
{
	unsigned long *id;
	unsigned long fundador;
	unsigned char *name;
	int score;
	unsigned int comment_count;
	int votes;
	// Either.
	unsigned char type; // 1 Q ; 2 A;
	void *special;		// parent Id. // answer count.
	struct bo *tags;
	struct no *ans;
	Date moment;

} * Post;

struct no
{
	Post pid;
	struct no *px;
};

struct bo
{
	unsigned long pid;
	struct bo *px;
};

// Métodos Publicos.

Post createPost();
void destroyPost(void *x);

void *postAnswer_transversal(Post x, void *(*p)(Post, void *), void *a);
void *postTag_transversal(Post x, int (*p)(unsigned int, void *), void *a);

unsigned long getP_id(Post x);
unsigned long *getP_id_point(Post x);
unsigned long getP_parentId(Post x);
unsigned long *getP_parentId_point(Post x);
unsigned long getP_fund(Post x);
unsigned char *getP_name(Post x);
unsigned int getP_ansCount(Post x);
int getP_score(Post x);
int getP_votes(Post x);
unsigned char getP_type(Post x);
unsigned int getP_nComment(Post x);
unsigned char *getP_name_point(Post x);
Date getP_date_point(Post x);
Date getP_date(Post x);

Post setP_id(Post x, unsigned long o);
Post setP_parentId(Post x, unsigned long o);
Post setP_fund(Post x, unsigned long f);
Post setP_ansCount(Post x, unsigned int n);
Post setP_name(Post x, const unsigned char *un);
Post setP_score(Post x, int s);
Post setP_type(Post x, unsigned char t);
Post setP_id(Post x, unsigned long o);
Post setP_upVote(Post x);
Post setP_downVote(Post x);
Post setP_date(Post x, int d, int m, int a);
Post setP_nComment(Post x, unsigned int n);
Post setP_addAns(Post x, Post val);
Post setP_tag(Post x, char *tag, void *set);

// Métodos privados.

static void null_check(void *x);
static struct bo *add_to_ll(struct bo *x, unsigned long val);

//-------------------------------------------------------------------------------------

static void null_check(void *x)
{
	if (x)
		g_free(x);
}

static struct bo *add_to_ll(struct bo *x, unsigned long val)
{
	struct bo *new = g_malloc(sizeof(struct bo));
	new->pid = val;
	new->px = x;
	return new;
}

//-------------------------------------------------------------------------------------

// construtores.
Post createPost()
{
	Post x = g_malloc(sizeof(struct post));
	x->name = NULL;
	x->type = 0;
	x->fundador = 0;
	x->score = 0;
	x->comment_count = 0;
	x->votes = 0;
	x->id = g_malloc(sizeof(unsigned long));
	x->special = NULL;
	x->ans = NULL;
	//x->data = g_malloc (sizeof(struct date));
	x->moment = createDate(0, 0, 0);
	x->tags = NULL;
	return x;
}

void destroyPost(void *x)
{
	struct no *cur1, *del1;
	struct bo *cur2, *del2;
	Post y = (Post)x;
	free_date(y->moment);
	null_check(y->name);
	g_free(y->id);
	null_check(y->special);

	del1 = y->ans;
	if (del1)
	{
		for (cur1 = del1->px; cur1; cur1 = cur1->px)
		{
			g_free(del1);
			del1 = cur1;
		}
		g_free(del1);
	}

	del2 = y->tags;
	if (del2)
	{
		for (cur2 = del2->px; cur2; cur2 = cur2->px)
		{
			g_free(del2);
			del2 = cur2;
		}
		g_free(del2);
	}

	g_free(y);
}

//travessias
void *postAnswer_transversal(Post x, void *(*p)(Post, void *), void *a)
{
	struct no *cur;

	if (x->type == 1)
		for (cur = x->ans; cur; cur = cur->px)
			a = p(cur->pid, a);
	return a;
}

void *postTag_transversal(Post x, int (*p)(unsigned int, void *), void *a)
{
	struct bo *cur;
	int r = 1;

	for (cur = x->tags; cur && r; cur = cur->px)
		r = p(cur->pid, a);

	return a;
}

// Post getters
unsigned long getP_id(Post x)
{
	unsigned long *y = x->id;
	return (*y);
}

unsigned long *getP_id_point(Post x)
{
	return (x->id);
}

unsigned long getP_parentId(Post x)
{
	unsigned long *y;
	if (x->type == 2)
	{ //answer
		y = x->special;
		return (*y);
	}
	return (0);
}

unsigned int getP_ansCount(Post x)
{
	unsigned int *y;
	if (x->type == 1)
	{ //questão.
		y = x->special;
		return (*y);
	}
	return 0;
}

unsigned long *getP_parentId_point(Post x)
{
	return ((unsigned long *)x->special);
}

unsigned long getP_fund(Post x)
{
	return (x->fundador);
}

unsigned char *getP_name(Post x)
{
	unsigned char *tmp = NULL;

	if (x->name)
	{

		tmp = (unsigned char *)g_memdup(x->name, sizeof(char) * (strlen((const char *)x->name) + 1));
	}
	return tmp;
}

unsigned char *getP_name_point(Post x)
{
	return x->name;
}

int getP_score(Post x)
{
	return (x->score);
}

int getP_votes(Post x)
{
	return (x->votes);
}

unsigned char getP_type(Post x)
{
	return (x->type);
}

unsigned int getP_nComment(Post x)
{
	return x->comment_count;
}

Date getP_date_point(Post x)
{
	// memória dinâmica.
	//return createDate( get_day(x->moment), get_month(x->moment), get_year(x->moment) ) ;
	return x->moment;
}

Date getP_date(Post x)
{
	// memória dinâmica.
	return createDate(get_day(x->moment), get_month(x->moment), get_year(x->moment));
}

// Post setters
Post setP_addAns(Post x, Post val)
{

	struct no *cur = g_malloc(sizeof(struct no));
	cur->px = x->ans;
	cur->pid = val;
	x->ans = cur;

	return x;
}

Post setP_tag(Post x, char *tag, void *set)
{
	char tmp[1024];
	char *l, *ret;
	int i;
	TAD_community com = (TAD_community)set;

	ret = strstr(tag, "<");
	while (ret)
	{
		ret++; // avançar o '<'
		i = 0;
		for (l = ret; *l && (*l != '>'); l++)
			tmp[i++] = *l;

		tmp[i] = '\0';
		x->tags = add_to_ll(x->tags, code_tag(com, tmp));
		ret = strstr(ret, "<");
	}

	return x;
}

Post setP_id(Post x, unsigned long o)
{
	unsigned long *y = x->id;
	*y = o;
	return x;
}

Post setP_parentId(Post x, unsigned long o)
{
	unsigned long *y;

	if (!x->special)
	{ // é null
		y = g_malloc(sizeof(unsigned long));
		*y = o;
		x->special = y;
	}
	else
	{
		y = x->special;
		*y = (unsigned int)o;
	}
	return x;
}

Post setP_ansCount(Post x, unsigned int n)
{
	unsigned int *y;

	y = g_malloc(sizeof(unsigned int));
	*y = n;
	x->special = y;
	return x;
}

Post setP_upVote(Post x)
{
	x->votes += 1;
	return x;
}

Post setP_downVote(Post x)
{
	x->votes -= 1;
	return x;
}

Post setP_nComment(Post x, unsigned int n)
{
	x->comment_count = n;
	return x;
}

Post setP_date(Post x, int d, int m, int a)
{

	free_date(x->moment);
	x->moment = createDate(d, m, a);
	return x;
}

Post setP_fund(Post x, unsigned long f)
{
	x->fundador = f;
	return x;
}

Post setP_name(Post x, const unsigned char *un)
{
	int lenz = (strlen((const char *)un) + 1);
	null_check(x->name);
	x->name = (unsigned char *)g_memdup(un, sizeof(char) * lenz);
	return x;
}

Post setP_score(Post x, int s)
{
	x->score = s;
	return x;
}

Post setP_type(Post x, unsigned char t)
{
	x->type = t;
	return x;
}

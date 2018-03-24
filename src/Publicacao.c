//#include "Publicacao.h"
#include <string.h>
#include "interface.h"
#include <glib.h>
//#include "Community.h"
#include "bArray.h"
//#include "date.h"

typedef struct post
{
	unsigned int *id;
	unsigned long fundador;
	unsigned char *name;
	unsigned int score;
	unsigned int comment_count;
	unsigned int fav;
	// Either.
	unsigned char type; // 1 Q ; 2 A;
	void *special;		// parent Id. // answer count.
	//bArray *tags;
	struct no *ans;

	Date moment;

} * Post;

struct no
{
	Post pid;
	struct no *px;
};

static void null_check(void *x)
{
	if (x)
		g_free(x);
}

// Métodos publicos.

Post createPost()
{
	Post x = g_malloc(sizeof(struct post));
	x->name = NULL;
	x->type = 0;
	x->fundador = 0;
	x->score = 0;
	x->comment_count = 0;
	x->fav = 0;
	x->id = g_malloc(sizeof(unsigned int));
	x->special = NULL;
	x->ans = NULL;
	//x->data = g_malloc (sizeof(struct date));
	x->moment = createDate(0, 0, 0);
	//x->tags = NULL;
	return x;
}

void destroyPost(void *x)
{
	struct no *cur, *del;
	Post y = (Post)x;
	free_date(y->moment);
	null_check(y->name);
	g_free(y->id);
	null_check(y->special);
	g_free(y);

	del = y->ans;

	if (del)
	{
		for (cur = del->px; cur; cur = cur->px)
		{
			g_free(del);
			del = cur;
		}
		g_free(del);
	}
}

//COMPARADORES

static int int_cmp(void *a, void *b, void *user_data)
{
	int *x = (int *)a;
	int *y = (int *)b;

	return (*y - *x);
}

static int date_compare(const void *a /*x*/, const void *b /*y*/, void *user_data)
{

	// user data será sempre null;
	Date x = (Date)a, y = (Date)b;

	if (get_year(x) > get_year(y))
		return 1;
	else if (get_year(x) < get_year(y))
		return -1;
	//-----------------------------------------
	if (get_month(x) > get_month(y))
		return 1;
	else if (get_month(x) < get_month(y))
		return -1;
	//-----------------------------------------
	if (get_day(x) > get_day(y))
		return 1;
	else if (get_day(x) < get_day(y))
		return -1;

	return 0;
}

int post_compare(void *a, void *b, void *user_data) // não vai ser preciso.
{

	Date x = ((Post)a)->moment;
	Date y = ((Post)b)->moment;

	return date_compare(x, y, user_data);
}

int inv_post_compare(void *a, void *b, void *user_data)
{

	return (-1) * post_compare(a, b, user_data);
}

int score_cmp(void *a, void *b, void *user_data)
{
	Post x = (Post)a;
	Post y = (Post)b;

	int anum, bnum;

	anum = (int)(x->score);
	bnum = (int)(y->score);

	return int_cmp(&anum, &bnum, user_data);
}

void *postAnswer_transversal(Post x, void* (*p)(Post, void *), void *a){
	struct no *cur;
	if( x->type == 1 ){
		for(cur = x->ans; cur; cur = cur->px )
			a = p( cur->pid , a );
	}

	return a;
}

////
// Post getters
unsigned int getP_id(Post x)
{
	unsigned int *y = x->id;
	return (*y);
}

unsigned int *getP_id_point(Post x)
{
	return (x->id);
}

unsigned int getP_parentId(Post x)
{
	unsigned int *y;
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

int nAns_cmp(void *a, void *b, void *user_data)
{
	Post x = (Post)a;
	Post y = (Post)b;

	int anum, bnum;

	anum = getP_ansCount(x);
	bnum = getP_ansCount(y);

	return int_cmp(&anum, &bnum, user_data);
}

unsigned int *getP_parentId_point(Post x)
{
	return ((unsigned int *)x->special);
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

		tmp = g_malloc(sizeof(unsigned char) * (strlen((const char *)x->name) + 1));
		strcpy((char *)tmp, (const char *)x->name);
	}
	return tmp;
}

unsigned int getP_score(Post x)
{
	return (x->score);
}

unsigned int getP_fav(Post x)
{
	return (x->fav);
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

Post setP_id(Post x, unsigned int o)
{
	unsigned int *y = x->id;
	*y = o;
	return x;
}

Post setP_parentId(Post x, unsigned int o)
{
	unsigned int *y;

	if (!x->special)
	{ // é null
		y = g_malloc(sizeof(unsigned int));
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

Post setP_fav(Post x, unsigned int n)
{
	x->fav = n;
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

Post setP_fund(Post x, long f)
{
	x->fundador = f;
	return x;
}

Post setP_name(Post x, const unsigned char *un)
{

	null_check(x->name);
	x->name = g_malloc(sizeof(unsigned char) * (strlen((const char *)un) + 1));
	strcpy((char *)x->name, (const char *)un);
	return x;
}

Post setP_score(Post x, unsigned int s)
{
	x->score = s;
	return x;
}

Post setP_type(Post x, unsigned char t)
{
	x->type = t;
	return x;
}

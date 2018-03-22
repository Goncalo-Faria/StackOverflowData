//#include "Publicacao.h"
#include <string.h>
#include "interface.h"
#include <glib.h>
#include "Community.h"
#include "bArray.h"
//#include <stdio.h>
//#include "date.h"

typedef struct post
{
	unsigned int *id;
	unsigned long fundador;
	unsigned char *name;
	unsigned int score;
	// Either.
	unsigned char type; // 1 Q ; 2 A;
	void *special;		// parent Id. // answer count.
	bArray *tags;
	Date moment;

} * Post;

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
	x->id = g_malloc(sizeof(unsigned int));
	x->special = NULL;
	//x->data = g_malloc (sizeof(struct date));
	x->moment = createDate(0, 0, 0);
	x->tags = NULL;
	return x;
}

Post create_array ( Post x , unsigned long t , char **strings  ) {
	int i;
	bArray a = initA( t , g_free );
	for (i=0; i <t ; i++) {
		add_to_A( t , (char *) *string );
		(**strings)++;
	}
	x->tags = a;
	return p;
}


void destroyPost(void *x)
{
	Post y = (Post)x;
	free_date(y->moment);
	null_check(y->name);
	g_free(y->id);
	null_check(y->special);
	g_free(y);
}


//COMPARADORES
int post_compare(void *a, void *b, void *user_data)// não vai ser preciso.
{

	Date x = getP_date_point((Post)a);
	Date y = getP_date_point((Post)b);

	return date_compare(x, y, user_data);
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

unsigned char getP_type(Post x)
{
	return (x->type);
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

Post incP_ansCount(Post x)
{
	unsigned int *y;

	if (x->type == 1)
	{
		if (!x->special)
		{

			y = g_malloc(sizeof(unsigned int));
			*y = 1;
			x->special = y;
		}
		else
		{
			y = x->special;
			*y = *y + 1;
		}
	}
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





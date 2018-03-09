#ifndef __PAIR_H__
#define __PAIR_H__
typedef struct str_pair* STR_pair;

STR_pair create_pair(char* fst, char* snd);
void set_fst(STR_pair pair, char* str);
void set_snd(STR_pair pair, char* str);
char* get_fst(STR_pair pair);
char* get_snd(STR_pair pair);
void free_pair(STR_pair pair);

// solução improvisada.

typedef struct long_pair* LONG_pair ;

#define inc_fstL(pair) set_fstL(pair, get_fstL(pair) + 1)
#define inc_sndL(pair) set_sndL(pair, get_sndL(pair) + 1)

LONG_pair create_pairL(long fst, long snd);
void set_fstL(LONG_pair pair, long a);
void set_sndL(LONG_pair pair, long a);
long get_fstL(LONG_pair pair);
long get_sndL(LONG_pair pair);
void free_pairL(LONG_pair pair);

#endif

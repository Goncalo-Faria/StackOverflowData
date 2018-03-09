#include <stdlib.h>
#include <string.h>
#include <common.h>
#include "pair.h"

struct str_pair {
  char* fst;
  char* snd;
};

STR_pair create_pair(char* fst, char* snd) {
  STR_pair p = malloc(sizeof(struct str_pair));
  p->fst = mystrdup(fst);
  p->snd = mystrdup(snd);
  return p;
}

void set_fst(STR_pair pair, char* str) {
  free(pair->fst);
  pair->fst = mystrdup(str);
}

void set_snd(STR_pair pair, char* str) {
  free(pair->snd);
  pair->snd = mystrdup(str);
}

char* get_fst(STR_pair pair) {
  return pair? mystrdup(pair->fst) : NULL;
}

char* get_snd(STR_pair pair) {
  return pair? mystrdup(pair->snd) : NULL;
}

void free_pair(STR_pair pair) {
  if(pair) {
    free(pair->fst);
    free(pair->snd);
    free(pair);
  }
}


struct long_pair {
  long fst;
  long snd;
};

LONG_pair create_pairL(long fst, long snd){
  LONG_pair p = malloc(sizeof(struct long_pair));
  p->fst = fst;
  p->snd = fst;
  return p;
}

void set_fstL(LONG_pair pair, long a){
  pair->fst = a;
}

void set_sndL(LONG_pair pair, long a){
  pair->snd = a;
}

long get_fstL(LONG_pair pair){
  return pair->fst;
}

long get_sndL(LONG_pair pair){
  return pair->snd;
}

void free_pairL(LONG_pair pair){
  free(pair);
}





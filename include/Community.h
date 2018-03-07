#ifndef community_h
#define community_h

#include <glib.h>


typedef struct TCD_community{
    GHashTable* user;
    GHashTable* post;
    GTree * treeP;
} * TAD_community;

#endif
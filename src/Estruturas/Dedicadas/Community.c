#include <glib.h>
#include <Community.c>

typedef struct TCD_community{
    GHashTable* user;
    GHashTable* post;
    GTree * treeP;
} * TAD_community;
#include <glib.h>
#include <Community.h>

typedef struct TCD_community{
    GHashTable* user;
    GHashTable* post;
    GTree * treeP;
} * TAD_community;
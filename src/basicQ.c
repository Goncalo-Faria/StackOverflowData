#include "interface.h"
#include <glib.h>
#include <Bloco.h>
#include <stdlib.h>
#include <string.h>

// Métodos publicos.
STR_pair info_from_post(TAD_community com, int id);



// Métodos privados.





STR_pair info_from_post(TAD_community com, int id){
    char* str1, *str2;
    Util y = NULL;
    Post x = NULL;
    STR_pair result;

    str1=malloc( sizeof(char)*100 );
    str2=malloc( sizeof(char)*100 );

    x = (Post)g_hash_table_lookup(com->post ,&id);
    strcpy(str1,(char*)x->nome);

    id = x->fundador;

    y = (Util)g_hash_table_lookup(com->user ,&id);
    strcpy(str2,(char*)y->nome);

    result = create_pair(str1,str2);

    free(str1);
    free(str2);

    return result;
}
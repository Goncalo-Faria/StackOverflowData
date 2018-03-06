#include <interface.h>
#include <libxml/parser.h>

typedef struct TCD_community{
    GHashTable* user;
    GHashTable* post;

} * TAD_community;

TAD_community init(){

    TAD_community x = malloc(sizeof(struct TCD_community));
    x->user = g_hash_table_new(g_int_hash,  g_int_equal);
    x->post = g_hash_table_new(g_int_hash,  g_int_equal);

    return x;
}

TAD_community load(TAD_community com, char* dump_path){

    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
    doc = xmlReadFile(strcat(dump_path ,"/Users.xml"), NULL, 0);

    if( !doc )
        perror("Could not parse the XML file\n");
    
    root_element = xmlDocGetRootElement(doc);

    parse(com)

}


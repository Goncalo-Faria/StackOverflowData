#include "interface.h"
#include <libxml/parser.h>

#include <stdio.h> // temporario
#include <string.h>
#include "Community.h"
#include <Bloco.h>

/**
 *  Main structure.
 * 
 * 
 * PostTypeId =1 pergunta;
 * 
 * PostTypeId = 2 resposta;
 * */


// Métodos publicos.
//TAD_community init();
//TAD_community clean(TAD_community com);
//TAD_community load(TAD_community com, char* dump_path)

// Métodos privados.
static void parsePost( TAD_community com, xmlNode * node);
static void parseUser( TAD_community com, xmlNode * node);

//

TAD_community init(){

    TAD_community x = malloc(sizeof(struct TCD_community));

    x->user = g_hash_table_new_full(g_int_hash,  g_int_equal, NULL, destroyUtil);
    x->post = g_hash_table_new_full(g_int_hash,  g_int_equal, NULL, destroyPost);

    return x;
}

TAD_community clean(TAD_community com){

      g_hash_table_destroy(com->user);
      g_hash_table_destroy(com->post);

      return com;
}

TAD_community load(TAD_community com, char* dump_path){

    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    char* tmpstr = malloc( sizeof(char)* (strlen(dump_path) + 10) ); 
    ////////////////////////////////////////////7
    sprintf(tmpstr,"%s/Users.xml",dump_path);
    doc = xmlReadFile(tmpstr, NULL, 0);

    if( !doc )
        perror("Could not parse the XML file\n");
    
    root_element = xmlDocGetRootElement(doc);

    parseUser(com, root_element);

    xmlFreeDoc(doc);
    xmlCleanupParser();
    xmlMemoryDump();
    ///////////////////////////////////////////////////////////////////
    
    sprintf(tmpstr,"%s/Posts.xml",dump_path);
    doc = xmlReadFile(tmpstr, NULL, 0);

    if( !doc )
        perror("Could not parse the XML file\n");
    
    root_element = xmlDocGetRootElement(doc);

    parsePost(com,root_element);
    printf("USER::%d \n",g_hash_table_size(com->post));
    
    free(tmpstr);

    xmlFreeDoc(doc);
    xmlCleanupParser();
    xmlMemoryDump();
    // x.............................................................
    return com;
}

static void parsePost ( TAD_community com , xmlNode* node ){

    xmlChar * hold;
    int num, ident;
    Util y = NULL;
    Post x = NULL;
    //unsigned long childCount = xmlChildElementCount(node),i;

    while(node){
        if(node->type == XML_ELEMENT_NODE && !xmlStrcmp( node->name , (const xmlChar*)"row") )
        {   
            //printf("%c%s\n",'-', node->name);
            //printf("%d\n",++e);
            x = (Post)createPost();

            // GET POST ID
            hold = xmlGetProp(node, (const xmlChar*)"Id");
            x->id = ident = (unsigned int) atoi((const char*) hold );
            xmlFree(hold);

            // GET POST TYPE
            hold = xmlGetProp(node, (const xmlChar*)"PostTypeId");
            x->type = (unsigned int) atoi((const char*) hold );
            xmlFree(hold);

            // GET OWNER ID
            hold = xmlGetProp(node, (const xmlChar*)"OwnerUserId");
            x->fundador = num = (unsigned int) atoi((const char*) hold );
            xmlFree(hold);

            // GET OWNER REF
            y = (Util)g_hash_table_lookup(com->user ,&num);
            
            // COUNT POST TYPE 
            if(x->type == 1)
                y->Q++;
            else 
                y->A++;
            
            // GET POST TITLE
            hold = xmlGetProp(node, (const xmlChar*)"Title");
            sprintf((char*)x->nome,"%s",(const char*)hold );
            xmlFree(hold);

            g_hash_table_insert(com->post , (void*)&ident, x );

        }

        parsePost(com , node->children);
        node = node->next;
    }
}

static void parseUser ( TAD_community com , xmlNode* node ){

    xmlChar * hold;
    Util x = NULL;
    int ident;
    //unsigned long childCount = xmlChildElementCount(node),i;

    while(node){
        if(node->type == XML_ELEMENT_NODE && !xmlStrcmp( node->name , (const xmlChar*)"row") )
        {   
            //printf("%c%s\n",'-', node->name);
            //printf("%d\n",++e);
            x = (Util)createUtil();

            // get user id
            hold = xmlGetProp(node, (const xmlChar*)"Id");
            x->id = ident =(unsigned int) atoi((const char*) hold );
            xmlFree(hold);
            
            // get Display name
            hold = xmlGetProp(node, (const xmlChar*)"DisplayName");
            sprintf((char*)x->nome,"%s",(const char*)hold );
            xmlFree(hold);

            g_hash_table_insert(com->user , (void*)(&ident), x );

        }

        parsePost(com , node->children);
        node = node->next;
    }
}
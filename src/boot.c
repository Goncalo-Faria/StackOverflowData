#include "interface.h"
#include <libxml/parser.h>

#include <stdio.h> // temporario
#include <string.h>
#include "Community.h"
#include <Bloco.h>
#include <glib.h>


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

// recebe uma avl tree e retira de la as datas , para um su-array defenido no glib
// estou a assumir que recebo uma AVL;

TAD_community load(TAD_community com, char* dump_path){

    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    char* tmpstr = g_malloc( sizeof(char)* (strlen(dump_path) + 10) ); 
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
    printf("USER::%d \n",postSet_size(com));
    
    g_free(tmpstr);

    xmlFreeDoc(doc);
    xmlCleanupParser();
    xmlMemoryDump();
    // x.............................................................
    return com;
}

static void parsePost ( TAD_community com , xmlNode* node ){

    xmlChar * hold;
    char buffer[100];
    long num;
    int dia, mes, ano ;
    unsigned int *Qid,*Aid, *ident;
    Util y = NULL;
    Post x = NULL;
    //unsigned long childCount = xmlChildElementCount(node),i;

    while(node){
        if(node->type == XML_ELEMENT_NODE && !xmlStrcmp( node->name , (const xmlChar*)"row") )
        {   
            //printf("%c%s\n",'-', node->name);
            //printf("%d\n",++e);
            x = (Post)createPost();
            ident = g_malloc ( sizeof( unsigned int ) );
            Qid   = g_malloc ( sizeof( unsigned int ) );

            // GET POST ID <LONG>
            hold = xmlGetProp(node, (const xmlChar*)"Id");
            *ident = (unsigned int) atoi((const char*) hold );
            xmlFree(hold);

            setP_id(x, *ident );

            // GET POST DATE
            hold = xmlGetProp(node, (const xmlChar*)"CreationDate");
            sscanf( (const char*)hold,"%d-%d-%d%s",&ano,&mes,&dia,buffer);
            xmlFree(hold);
            setP_date(x, dia,mes,ano);

            // GET POST TYPE
            hold = xmlGetProp(node, (const xmlChar*)"PostTypeId");
            setP_type ( x , (unsigned char) atoi((const char*) hold ) );
            xmlFree(hold);

            // GET OWNER ID
            hold = xmlGetProp(node, (const xmlChar*)"OwnerUserId");
            num = (unsigned long) atol((const char*) hold );
            setP_fund( x, num );
            xmlFree(hold);


            // ADD SCORE.
            hold = xmlGetProp(node, (const xmlChar*)"Score");
            setP_score(x ,(unsigned int) atoi((const char*) hold ));
            xmlFree(hold);



            // GET OWNER REF
            y = userSet_lookup(com , num);
            
            // COUNT POST TYPE 
            if( getP_type(x) == 1)
                inc_Q(y);
            else 
                inc_A(y);

        /*
                Passa para o parent id.
        
        */
        
            if( getP_type(x) == 1 ){ // Questão.
                *Qid = *ident;
                if ( !Q_belongs_hash(y ,*Qid) )// verifica se existe!
                    add_toBacia(y , Qid , NULL );

            /**
             * Se o user for o owner da Q info é null.
             * 
             * Caso contrário tem um apontador para o post id da resposta.
             *   
             */
            else
                g_free(Qid);
            //
            } else {
                if ( !A_belongs_hash(y ,*ident) ){// verifica se existe!

                    hold = xmlGetProp(node, (const xmlChar*)"ParentId");
                    *Qid = (unsigned int) atoi((const char*) hold );
                    xmlFree(hold);

                    Aid  = g_malloc( sizeof( unsigned int) );
                    *Aid = *ident; // valor da resposta.

                    add_toBacia(y , Qid , Aid);
                }
                else 
                    g_free(Qid);
            }         
            // GET POST TITLE
            hold = xmlGetProp(node, (const xmlChar*)"Title");
            setP_name( x, ( unsigned char* )hold );
            xmlFree(hold);

            postTree_insert(com, getP_date_point(x) , x );
            postSet_insert(com , ident, x );
        }

        parsePost(com , node->children);
        node = node->next;
    }
}

static void parseUser ( TAD_community com , xmlNode* node ){

    xmlChar * hold;
    Util x = NULL;
    unsigned long *ident;
    //unsigned long childCount = xmlChildElementCount(node),i;

    while(node){
        if(node->type == XML_ELEMENT_NODE && !xmlStrcmp( node->name , (const xmlChar*)"row") )
        {   
            x = (Util)createUtil();
            ident = g_malloc ( sizeof( unsigned long ));

            // get user id
            hold = xmlGetProp(node, (const xmlChar*)"Id");
            *ident = (unsigned long) atol((const char*) hold );
            xmlFree(hold);
            
            // GET UTIL BIO
            hold = xmlGetProp(node, (const xmlChar*)"AboutMe");
            setU_bio(x, (unsigned char*)hold );
            xmlFree(hold);

            // get Display name
            hold = xmlGetProp(node, (const xmlChar*)"DisplayName");
            setU_name(x, (unsigned char*)hold );
            xmlFree(hold);

            userSet_insert( com, ident, x );
        }

        parsePost(com , node->children);
        node = node->next;
    }
}

//#include "interface.h"
#include <libxml/parser.h>

#include <stdio.h> // temporario
#include <string.h>
#include <ctype.h>
#include "Community.h"
//#include <Bloco.h>
#include <glib.h>


/**
 *  Main structure.
 * 
 * 
 * PostTypeId =1 pergunta;
 * 
 * PostTypeId = 2 resposta;
 * */
static int u;

#define convert_to_lowercase(p,str) for( (p)=(str) ; *(p)!='\0'; (p)++) *(p) = tolower(*(p))
typedef void (*parse_function) (TAD_community , const xmlNode*);

// Métodos publicos.
//TAD_community init();
//TAD_community clean(TAD_community com);
//TAD_community load(TAD_community com, char* dump_path)

// Métodos privados.
//static void parsePost( TAD_community com, xmlNode * node);
static void parseUser( TAD_community com, const xmlNode * node);
static void parser ( TAD_community com , char* dump_path, char* file_name , parse_function f  );
static void parsePost ( TAD_community com , const xmlNode* node );
//

// recebe uma avl tree e retira de la as datas , para um su-array defenido no glib
// estou a assumir que recebo uma AVL;

TAD_community load(TAD_community com, char* dump_path){

    u=0;
    parser(com, dump_path, "Users", parseUser);
    printf("USER::%d \n",userSet_size(com));
    //parser(com, dump_path, "Posts", parsePost);

    //printf("USER::%d \n",postSet_size(com));
    /*
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
    */
    return com;
}

static void parsePost ( TAD_community com , const xmlNode* node ){

    xmlChar * hold;
    char buffer[100];
    long num;
    int dia, mes, ano ;
    unsigned int *Qid,*Aid, *ident;
    Util y = NULL;
    Post x = NULL;
    //unsigned long childCount = xmlChildElementCount(node),i;
 
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
    //printf("%s\n",(char*)hold);
    xmlFree(hold);



    // GET OWNER REF
    y = userSet_lookup(com , num);
            
    // COUNT POST TYPE 
    if( getP_type(x) == 1)
        inc_Q(y);
    else 
        inc_A(y);

    if( getP_type(x) == 1 ){ // Questão.
        *Qid = *ident;
        if ( !Q_belongs_hash(y ,*Qid) )// verifica se existe!
            add_toBacia(y , Qid , NULL );
    
        else
            g_free(Qid);
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
    
    if(hold){
        setP_name(x, (unsigned char*)hold );
        xmlFree(hold);
    }

    printf("%d",++u);
    postTree_insert(com, getP_date_point(x) , x );
    postSet_insert(com , ident, x );

}

static void parseUser ( TAD_community com , const xmlNode* node ){

    xmlChar * hold=NULL;
    Util x = NULL;
    unsigned long *ident;
    //unsigned long childCount = xmlChildElementCount(node),i;
    //printf("erros\n");
    x = (Util)createUtil();
    ident = g_malloc ( sizeof( unsigned long ));

            // get user id
    hold = xmlGetProp(node, (const xmlChar*)"Id");
    *ident = (unsigned long) atol((const char*) hold );
    //printf("%d \n",(int)*ident);
    xmlFree(hold);
            
            // GET UTIL BIO
    hold = xmlGetProp(node, (const xmlChar*)"AboutMe");
    
    if(hold ){
        setU_bio(x, (unsigned char*)hold );
        //printf("%s \n",(char*)hold);
        xmlFree(hold);
    }

            // get Display name
    hold = xmlGetProp(node, (const xmlChar*)"DisplayName");
    setU_name(x, (unsigned char*)hold );
    xmlFree(hold);



    userSet_insert( com, ident, x );
    return;
}
//file
//parsefunction

static void parser ( TAD_community com , char* dump_path, char* file_name , parse_function f ){

    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
    xmlNode *node = NULL;
    char* p;
    
    char* docname = g_malloc( sizeof(char)* ( strlen(dump_path) + strlen(file_name) + 6) ); 
    ////////////////////////////////////////////7
    sprintf(docname,"%s/%s.xml",dump_path,file_name);

    //printf("%s\n",tmpstr);
    doc = xmlParseFile(docname);

    if( !doc )
        perror("Erro no parse do documento XML.\n");
    
    root_element = xmlDocGetRootElement(doc);

    if ( !root_element ) {
        perror("Documento vazio.\n");
        xmlFreeDoc(doc);
        return;
    }
    node = root_element;
    strcpy(docname,file_name);
    convert_to_lowercase(p,docname);

    if (xmlStrcmp(node->name, (const xmlChar *) docname) ) {
        perror("Documento do tipo errado.\n");
        xmlFreeDoc(doc);
        return;
    }
    node = node->xmlChildrenNode;
    while (node != NULL) {
        if ((!xmlStrcmp(node->name, (const xmlChar *)"row"))){
            //perror("->alivde\n");
            f(com , node);
            //printf("%d -> size \n ",userSet_size(com) );
        }
        node = node->next;
    }

    g_free(docname);
    xmlFreeDoc(doc);

    xmlCleanupParser();
    xmlMemoryDump();
    return;
}
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
#define getAtr(hold,n,str) hold = xmlGetProp(n, (const xmlChar*)str)

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
static void parseHistory ( TAD_community com, const xmlNode* node);
//

// recebe uma avl tree e retira de la as datas , para um su-array defenido no glib
// estou a assumir que recebo uma AVL;

TAD_community load(TAD_community com, char* dump_path){

    //Util y;
    //Post x;

    //unsigned char* bio,*name;
    parser(com, dump_path, "Users", parseUser);
    printf("Number of users loaded ::%d \n",userSet_size(com));
    parser(com, dump_path, "Posts", parsePost);
    printf("Number of posts loaded ::%d \n",postSet_size(com));
    parser(com, dump_path, "PostHistory", parseHistory);
    printf("\n.. Loading Terminaterd ..\n");

    /*
    y = userSet_lookup( com, 91872 );
    bio = getU_bio(y);
    name = getU_name(y);
    if(name){
        printf("%s\n",(char*)name);
    }
    
    if(bio){
        printf("%s\n",(char*)bio);
    }
    x = postSet_lookup(com, 97086);

    name=  getP_name(x);
    if(name){
        printf("%s\n",(char*)name);
        printf("type : %d \n",getP_type(x));
    }

    printf("Este utilizador deixa-m especialmente preocupado.\n");
    */
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

static void parser ( TAD_community com , char* dump_path, char* file_name , parse_function f ){

    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
    xmlNode *node = NULL;
    char* p;
    //int count=50000;
    
    char* docname = g_malloc( sizeof(char)* ( strlen(dump_path) + strlen(file_name) + 6) ); 
    ////////////////////////////////////////////7
    sprintf(docname,"%s/%s.xml",dump_path,file_name);

    printf("%s\n",docname);
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

    if( !strcmp("users",docname) )
        node=node->next->next; // passar a frente o user negativo.

    while (node != NULL ) {
        if ((!xmlStrcmp(node->name, (const xmlChar *)"row"))){
            //perror("->alivde\n");
            f(com , node);
            
        }
        node = node->next;
    }

    g_free(docname);
    xmlFreeDoc(doc);

    xmlCleanupParser();
    xmlMemoryDump();
    return;
}

static void parsePost ( TAD_community com , const xmlNode* node ){

    xmlChar * hold;
    char buffer[100];
    int dia, mes, ano ;
    //unsigned int *ident;
    Post x = NULL;
    x = (Post)createPost();
    //ident = g_malloc ( sizeof( unsigned int ) );

    // GET POST ID <LONG> getatr( hold , n , str )

    getAtr(hold,node,"Id");
    setP_id( x, (unsigned int) atoi((const char*) hold ) );
    xmlFree(hold);

    // printf( " id: : %d \n",getP_id(x) );
    //printf("cool\n");
            // GET POST DATE
    getAtr(hold,node,"CreationDate");
    sscanf( (const char*)hold,"%d-%d-%d%s",&ano,&mes,&dia,buffer);
    xmlFree(hold);
    setP_date(x, dia,mes,ano);

            // GET POST TYPE
    getAtr(hold,node,"PostTypeId");
    setP_type ( x , (unsigned char) atoi((const char*) hold ) );
    xmlFree(hold);

    if( getP_type(x)>2 ){
        //printf("trigger\n");
        destroyPost(x);
        return;
    }

    if( getP_type(x) == 2 ){// ans
        getAtr(hold,node,"ParentId");
        setP_parentId( x ,(unsigned int) atoi((const char*) hold ) );
        xmlFree(hold);
    }
    // ADD SCORE.
    getAtr(hold,node,"Score");
    setP_score(x ,(int) atoi((const char*) hold ));
    //printf("%s\n",(char*)hold);
    xmlFree(hold);

    // GET OWNER REF

    // GET POST TITLE
    getAtr(hold,node,"Title");
    if(hold){
        setP_name(x, (unsigned char*)hold );
        xmlFree(hold);
    }

    postTree_insert(com, getP_date_point(x) , x );
    postSet_insert(com , getP_id_point(x) , x );

}

static void parseUser ( TAD_community com , const xmlNode* node ){

    xmlChar * hold=NULL;
    Util x = NULL;
    //unsigned long childCount = xmlChildElementCount(node),i;
    //printf("erros\n");
    x = (Util)createUtil();
    //ident = g_malloc ( sizeof( unsigned long ));

            // get user id
    
    getAtr(hold,node,"Id");    
    setU_id( x, (unsigned long ) atol((const char*) hold ) );
    xmlFree(hold);
    
            // GET UTIL BIO
    getAtr(hold,node,"AboutMe");
    
    if(hold){
        setU_bio(x, (unsigned char*)hold );
        //printf("%s \n",(char*)hold);
        xmlFree(hold);
    }

            // get Display name
    getAtr(hold,node,"DisplayName");
    setU_name(x, (unsigned char*)hold );
    xmlFree(hold);

    userSet_insert_id( com, getU_id_point(x) , x );
    userSet_insert_name( com, getU_name_point(x) , x );
    return;
}

static void parseHistory ( TAD_community com, const xmlNode* node){

    xmlChar * hold=NULL;
    Util x = NULL;
    Post y,tmp = NULL;
    unsigned long userId;
    unsigned int postId;
    unsigned int hType;
    unsigned char *name;


    getAtr(hold,node,"PostHistoryTypeId");
    hType = (unsigned int) atoi((const char*) hold );
    xmlFree(hold);

    if(hType != 1)
        return;

    getAtr(hold,node,"UserId");
    if(hold){
        userId = (unsigned long) atol((const char*) hold );
        xmlFree(hold);

        x = userSet_id_lookup(com, userId);
        if ( !x ) return;

    } else {
        getAtr(hold,node,"UserDisplayName");
        name = (unsigned char*)hold; 
        
        x = userSet_name_lookup(com, name );
        xmlFree(hold);
        if ( !x ) return;
        userId = getU_id(x);
    }

    getAtr(hold,node,"PostId");
    postId = (unsigned int) atoi((const char*) hold );
    xmlFree(hold);

    y = postSet_lookup(com, postId);

    if ( !y ) return;

    if( getP_type(y) == 1 ){
        incU_Q(x);
    }

    if( getP_type(y) == 2 ){
        incU_A(x);
        
        // Acrescentar ao numero de respostas.
        //tmp = postSet_lookup(com, getP_parentId(y) );
    }

    setP_fund(y, userId);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    bind_toBacia(x,y);//
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  

    return;
}

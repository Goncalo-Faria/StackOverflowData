#include <libxml/parser.h>
#include "Publicacao.h"
#include <interface.h>
#include <string.h>
#include <ctype.h>
#include "Community.h"
#include <glib.h>

//-------------------------------------------------------------------------------------
    // Da autoria de Gonçalo Faria && Guilherme Viveiros.
//-------------------------------------------------------------------------------------

//defines
#define getAtr(hold, n, str) hold = xmlGetProp(n, (const xmlChar *)str)

#define convert_to_lowercase(p, str)       \
    for ((p) = (str); *(p) != '\0'; (p)++) \
    *(p) = tolower(*(p))

typedef TAD_community (*parse_function)(TAD_community, const xmlNode *);

// Métodos publicos.
TAD_community load(TAD_community com, char *dump_path); // #0

//Métodos privados.
static TAD_community parser(TAD_community com, char *dump_path, char *file_name, parse_function f);

static TAD_community parseUser(TAD_community com, const xmlNode *node);
static TAD_community parsePost(TAD_community com, const xmlNode *node);
static TAD_community parseTag(TAD_community com, const xmlNode *node);
static TAD_community parseVotes(TAD_community com, const xmlNode *node);

static TAD_community reduce(TAD_community com);
static void link(void *key, void *value, void *user_data);
static void adder(void *key, void *value, void *user_data);

//-------------------------------------------------------------------------------------

static void adder(void *key, void *value, void *user_data)
{
    TAD_community com = (TAD_community)user_data;
    /**
     * Adiciona ao bArray.
    */
    insert_array(com, (Post)value);
}

static TAD_community reduce(TAD_community com)
{
    com = (TAD_community)postSet_transversal(com, link, (void *)com); // aplica link a todos os elementos do conjunto das publicações.
    return finalize_array(com); // ordena o bArray cronologicamente
}

static void link(void *key, void *value, void *user_data)
{
    Post par, pub = (Post)value;
    TAD_community com = (TAD_community)user_data;
    Util usr;
    unsigned long founder = getP_fund(pub);

    if (founder)
    {
        usr = userSet_id_lookup(com, founder);
        if (usr)
        {   
            // Contagem no numero de perguntas des user.
            if (getP_type(pub) == 1)
                usr = incU_Q(usr);
            else
            {   
                /**
                 * Contagem do numero de respostas.
                */
                usr = incU_A(usr);
                /**
                 * Adiciona a resposta em questão ao conjunto das respostas à sua pergunta.
                 * */
                par = postSet_lookup(com, getP_parentId(pub));
                if (par)
                    par = setP_addAns(par, pub);
            }
            // adicionado ao conjunto de intervenção deste utilizador.
            usr = bind_toBacia(usr, pub); //
        }
    }
    adder(key, value, com);
}

static TAD_community parser(TAD_community com, char *dump_path, char *file_name, parse_function f)
{
    /**
     *  Esta função cria uma árvore de parse, de um ficheiro inserido , com o libxml
     *  e itera nos elementos com o atributo 'row' e aplica 'parse_function' a todos o s elementos.
     **/
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
    xmlNode *node = NULL;
    char *p;
    //int count=50000;

    char *docname = g_malloc(sizeof(char) * (strlen(dump_path) + strlen(file_name) + 6));
    ////////////////////////////////////////////7
    sprintf(docname, "%s/%s.xml", dump_path, file_name);

    doc = xmlParseFile(docname);

    if (!doc)
        return com;

    root_element = xmlDocGetRootElement(doc);

    if (!root_element)
    {
        xmlFreeDoc(doc);
        return com;
    }
    node = root_element;
    strcpy(docname, file_name);
    convert_to_lowercase(p, docname);

    if (xmlStrcmp(node->name, (const xmlChar *)docname))
    {
        xmlFreeDoc(doc);
        return com;
    }
    node = node->xmlChildrenNode;

    if (!strcmp("users", docname))
        node = node->next->next; // passar a frente o user negativo.

    while (node != NULL)
    {
        if ((!xmlStrcmp(node->name, (const xmlChar *)"row")))
        {
            //perror("->alivde\n");
            com = f(com, node);
        }
        node = node->next;
    }

    g_free(docname);
    xmlFreeDoc(doc);

    xmlCleanupParser();
    //xmlMemoryDump();
    return com;
}

static TAD_community parsePost(TAD_community com, const xmlNode *node)
{
    /**
     * Esta função é executada a todos os elementos com atributo row do ficheiro Post.xml.
     * Esta incarrega-se de coletar os dados necessários deste ficheiro e colocalos em Community. 
     * */
    xmlChar *hold;
    char buffer[100];
    int dia, mes, ano;
    Post x = NULL;
    x = (Post)createPost();

    // GET POST ID
    getAtr(hold, node, "Id");
    x = setP_id(x, (unsigned long)atol((const char *)hold));
    xmlFree(hold);

    // GET POST DATE
    getAtr(hold, node, "CreationDate");
    sscanf((const char *)hold, "%d-%d-%d%s", &ano, &mes, &dia, buffer);
    xmlFree(hold);
    x = setP_date(x, dia, mes, ano);

    // GET POST TYPE
    getAtr(hold, node, "PostTypeId");
    x = setP_type(x, (unsigned char)atoi((const char *)hold));
    xmlFree(hold);

    if (getP_type(x) > 2)
    {
        destroyPost(x);
        return com;
    }

    // RESPOSTA
    if (getP_type(x) == 2)
    { // ans
        getAtr(hold, node, "ParentId");
        x = setP_parentId(x, (unsigned long)atol((const char *)hold));
        xmlFree(hold);

        getAtr(hold, node, "CommentCount");

        x = setP_nComment(x, (unsigned int)atoi((const char *)hold));
        //printf("%s\n",(char*)hold);
        xmlFree(hold);
    }
    else
    {   
        // PERGUNTA.
        getAtr(hold, node, "AnswerCount");
        x = setP_ansCount(x, (unsigned int)atoi((const char *)hold));
        xmlFree(hold);
    }
    // ADD TAGS
    getAtr(hold, node, "Tags");
    if (hold)
    {
        x = setP_tag(x, (char *)hold, com);
        xmlFree(hold);
    }
    // ADD SCORE.
    getAtr(hold, node, "Score");
    x = setP_score(x, (int)atoi((const char *)hold));
    xmlFree(hold);

    // GET POST TITLE
    getAtr(hold, node, "Title");
    if (hold)
    {
        x = setP_name(x, (unsigned char *)hold);
        xmlFree(hold);
    }

    getAtr(hold, node, "OwnerUserId");
    if (hold)
    {
        x = setP_fund(x, (unsigned long)atol((const char *)hold));
        xmlFree(hold);
    }

    return postSet_insert(com, getP_id_point(x), x);
}

static TAD_community parseUser(TAD_community com, const xmlNode *node)
{
    /**
     * Esta função é executada a todos os elementos com atributo row do ficheiro User.xml.
     * Esta incarrega-se de coletar os dados necessários deste ficheiro e colocalos em Community. 
     **/

    xmlChar *hold = NULL;
    Util x = NULL;
    x = (Util)createUtil();

    // USER ID
    getAtr(hold, node, "Id");
    x = setU_id(x, (unsigned long)atol((const char *)hold));
    xmlFree(hold);

    // GET UTIL BIO
    getAtr(hold, node, "AboutMe");

    if (hold)
    {
        x = setU_bio(x, (unsigned char *)hold);
        xmlFree(hold);
    }

    // REPUTAÇAO
    getAtr(hold, node, "Reputation");
    x = setU_rep(x, (int)atoi((const char *)hold));
    xmlFree(hold);

    // GET UTIL NAME
    getAtr(hold, node, "DisplayName");
    x = setU_name(x, (unsigned char *)hold);
    xmlFree(hold);

    com = userSet_insert_id(com, getU_id_point(x), x);
    return com;
}

static TAD_community parseTag(TAD_community com, const xmlNode *node)
{
    /**
     * Esta função é executada a todos os elementos com atributo row do ficheiro Tags.xml.
     * Esta incarrega-se de coletar os dados necessários deste ficheiro e colocalos em Community. 
     **/

    xmlChar *hold = NULL;
    unsigned long id;

    // GET TAG ID
    getAtr(hold, node, "Id");
    id = (unsigned long)atol((const char *)hold);
    xmlFree(hold);

    // GET TAG NAME.
    getAtr(hold, node, "TagName");
    com = assign_tag(com, (char *)hold, id);
    xmlFree(hold);

    return com;
}

static TAD_community parseVotes(TAD_community com, const xmlNode *node)
{   
    /**
     * Esta função é executada a todos os elementos com atributo row do ficheiro Votes.xml.
     * Esta incarrega-se de coletar os dados necessários deste ficheiro e colocalos em Community. 
     **/

    xmlChar *hold = NULL;
    int c;
    Post x;

    // GET VOTE TYPE
    getAtr(hold, node, "VoteTypeId");
    c = (int)atoi((const char *)hold);
    xmlFree(hold);

    if (c == 2)
    {
        getAtr(hold, node, "PostId");
        x = postSet_lookup(com, (unsigned long)atol((const char *)hold));
        xmlFree(hold);
        // SET UPVOTE
        if (x)
            x = setP_upVote(x);
    }
    else if (c == 3)
    {
        getAtr(hold, node, "PostId");
        x = postSet_lookup(com, (unsigned long)atol((const char *)hold));
        xmlFree(hold);
        // SET DOWNVOTE.
        if (x)
            x = setP_downVote(x);
    }

    return com;
}

//-------------------------------------------------------------------------------------

TAD_community load(TAD_community com, char *dump_path)
{
    TAD_community tmp;
    
    // load das tags
    tmp = parser(com, dump_path, "Tags", parseTag);
    if (!tmp)
        return com;
    else
        com = tmp;
    // load dos utilizadores
    tmp = parser(com, dump_path, "Users", parseUser);
    if (!tmp)
        return com;
    else
        com = tmp;

    // load dos posts
    tmp = parser(com, dump_path, "Posts", parsePost);
    if (!tmp)
        return com;
    else
        com = tmp;

    // load dos votos.
    tmp = parser(com, dump_path, "Votes", parseVotes);
    if (!tmp)
        return com;
    else
        com = tmp;

    com = turnOn_array(com, (unsigned long)postSet_size(com));
    com = reduce(com);
    com = activate(com);
    return com;
}

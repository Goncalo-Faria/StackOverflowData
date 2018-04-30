#include <glib.h>
#include <string.h>
#include "Community.h"
#include "bArray.h"
#include <comondec.h>

//-------------------------------------------------------------------------------------
    // Da autoria de Gonçalo Faria && Guilherme Viveiros.
//-------------------------------------------------------------------------------------

// Estruturas privadas.
struct no
{
    unsigned long pid;
    struct no *px;
};

typedef struct bo
{
    float key;
    Post pid;

} * Box;

// Métodos Publicos
LONG_list both_participated(TAD_community com, long id1, long id2, int N);        //#9
long better_answer(TAD_community com, long id);                                   //#10
LONG_list questions_with_tag(TAD_community com, char *tag, Date begin, Date end); //#4

// Métodos Privados.
static Box createBox(float key, Post pid);
static float rank(TAD_community com, Post x);
static void intr(void *key, void *value, void *user_data);
static void *travel(Post x, void *user_data);
static void collect_tag(void *value, void *user_data);
static int tag_eq(unsigned int pid, void *user_data);

//-------------------------------------------------------------------------------------

static Box createBox(float key, Post pid)
{
    /**
     * Instância a estrutura box.
     * 
    */
    Box send = g_malloc(sizeof(struct bo));

    send->key = key;
    send->pid = pid;
    return send;
}

static float rank(TAD_community com, Post x) 
{
    float r;
    unsigned long founder;
    Util u;
    float rep, vot, cmm, scr;

    /**
     * Calcula a expressão referida na interrogação 10. 
     * 
    */
    founder = getP_fund(x);
    if (founder)
    {
        u = userSet_id_lookup(com, founder);
        if (u)
        {
            rep = (float)getU_rep(u);
            vot = (float)getP_votes(x);
            cmm = (float)getP_nComment(x);
            scr = (float)getP_score(x);

            r = rep * 0.25 + vot * 0.2 + cmm * 0.1 + scr * 0.45;
        }
        else
        {
            r = 0;
        }
    }
    else
    {
        r = 0;
    }

    return r;
}

static void intr(void *key, void *value, void *user_data)
{
    Record box = (Record)user_data;
    Record ll = (Record)getFst(box);
    int *counter = (int *)getSnd(ll);
    struct no **cur = (struct no **)getFst(ll);
    struct no *new;
    Util lrg = (Util)getSnd(box);
    unsigned long pst = *(unsigned long *)key;

    /**
     * Se o elementos em questão estiverem contidos também na rede de intervenção 
     * da publicação do outro utilizador.
     * A publicação é adicionada à lista ligada que regista o interseção.
     * */
    if (toBacia_contains(lrg, pst))
    {
        new = g_malloc(sizeof(struct no));
        new->pid = pst;
        new->px = *cur;
        *cur = new;
        *counter += 1;
    }
}

static void *travel(Post x, void *user_data)
{
    Record cur = (Record)user_data;
    TAD_community com = (TAD_community)getFst(cur);
    Box a = (Box)getSnd(cur);
    float r;

    /**
     * É calculada a formula de rankeamento. 
     */
    r = rank(com, x);

    /**
     * Se for maior que o presente valor substitui-o.
     * 
    */
    if (a)
    {
        if (r > a->key)
        {
            a->key = r;
            a->pid = x;
        }
    }
    else
    {
        cur = setSnd(cur, createBox(r, x));
    }

    return (void *)cur;
}

static int tag_eq(unsigned int pid, void *user_data)
{
    unsigned int *tag_id = (unsigned int *)getSnd((Record)getFst((Record)user_data));
    int *flag = (int *)getSnd((Record)user_data);

    /**
     *  Esta função é aplicada aos elementos no conjunto das tags até que 
     *  uma delas seja igual à introoduzida.
     */
    if (pid == *tag_id)
    {
        *flag = 0;
    }

    return *flag;
}

static void collect_tag(void *value, void *user_data)
{
    struct no *new, **ll;
    unsigned int *n;
    int flag = 1;
    Record box = createRecord(user_data, &flag);
    box = postTag_transversal((Post)value, tag_eq, box);
    /**
     * Enquanto os elementos de publicação são percorrido. 
     * O conjunto de tags da publicação em questão é atravessado e é registada a ocorrência desta. 
     */

    Record list = (Record)getFst((Record)getFst(box));

    ll = (struct no **)getFst(list);
    n = (unsigned int *)getSnd(list);

    if (!flag)
    {
        /**
         * Esta publicação contem a tag. 
         */
        new = g_malloc(sizeof(struct no));
        new->px = *ll;
        new->pid = (unsigned long)getP_id((Post)value);
        *ll = new;
        *n += 1;
    }
    g_free(box);
}
//-------------------------------------------------------------------------------------

LONG_list both_participated(TAD_community com, long id1, long id2, int N)
{
    Util usr1, usr2;
    int p, pred, req = N;
    Record box;
    Util sml, lgr;
    HEAP hp;
    bArray b;
    Post u;
    struct no *del, *x, *cur = NULL;

    LONG_list ll;
    if (is_ON(com))
    { /**
        * Foi efetuado com sucesso a leitura dos ficheiro xml.
        */
        usr1 = userSet_id_lookup(com, id1);
        usr2 = userSet_id_lookup(com, id2);

        /**
         * Obtêm do conjunto os elementos descriminados nos argumentos da função.
        */
        if (usr1 && usr2)
        {
            /**
             * Os referidos utilizadores existem. 
             */
            p = toBacia_size(usr1) > toBacia_size(usr2);

            sml = p ? usr2 : usr1;
            lgr = p ? usr1 : usr2;
            p = 0;
            /**
             * Seleciona qual desses dois utilizadores contêm um numero inferior de publicações
             * onde esteve diretamente envolvido.  
             */

            box = createRecord(createRecord(&cur, &p), lgr);
            box = toBacia_transversal(sml, intr, box);

            /**
             * O conjunto de publicações do utilizador com menor numero de envolvimento
             * tem  estas percorridas onde é aplicada intr a cada elemento.
             * É gerada uma lista ligada que contêm o id perguntas em que ambos estiveram envolvidos.
             */
            pred = (p < N);
            N = pred ? p : N;

            /**
             * Os elementos são removidos da lista ligada e são adicionadas as todas as publicações cujo identifacor
             * se encontra nesta a um bArray.
             */
            b = init_A((unsigned long)N, NULL);
            del = NULL;

            for (x = cur; N--; x = x->px)
            {

                if (del)
                    g_free(del);

                u = postSet_lookup(com, x->pid);
                if (u)
                    b = add_to_A(b, (void *)u);

                del = x;
            }

            if (del)
                g_free(del);

            /**
             * Este bArray é percorrido e é criada uma fila de prioridade de cronologia inversa.
             */
            if (!pred)
            { // ainda tem elementos a lista.
                hp = Generalized_Priority_Queue(b, length_A(b), inv_post_compare, yes, NULL);
                cur = x;
                ll = create_list(req);

                del = NULL;

                for (x = cur; x; x = x->px)
                {
                    if (del)
                        g_free(del);

                    u = postSet_lookup(com, x->pid);
                    if (u)
                        hp = add_in_Place_H(hp, u);

                    del = x;
                }
                if (del)
                    g_free(del);

                /**
                 *  Conversão para os tipos esperados na interrogação.
                 * 
                 */
                p = 0;
                N = length_H(hp);
                while (!empty_H(hp))
                {
                    u = rem_Heap(hp);
                    set_list(ll, N - 1 - p++, (long)getP_id(u));
                }

                while ( p < req )
                    set_list(ll, p++, 0);

                destroy_H(hp);
            }
            else
            { /**
                 * Caso o bArray tenha sido totalmente preenchido é ordenado.
                 */
                b = sort_A(b, post_ord);
                N = length_A(b);
                ll = create_list(req);

                for (p = 0; p < N; p++)
                {
                    u = get_atA(b, p);
                    set_list(ll, N - 1 - p, (long)getP_id(u));
                }
                while( p < req)
                    set_list(ll, p++, 0);

            }
        }
        else
            return NULL;

        destroy_A(b);
        g_free(getFst(box));
        g_free(box);

        return ll;
    }
    else
        return NULL;
}

long better_answer(TAD_community com, long id)
{
    Record a;
    Box bx;
    Post p;
    long ll;

    if (is_ON(com))
    {
        /**
        * Foi efetuado com sucesso a leitura dos ficheiro xml.
        */
        p = postSet_lookup(com, (unsigned long)id);

        if (p && (getP_type(p) == 1))
        {
            /**
             * A publicação foi consultada com sucesso e é uma pergunta. 
             */
            a = createRecord((void *)com, NULL);

            /**
             * O conjunto das reposta da publicação recebida é percorrido
             * e é aplicado travel a todos os elementos.
             * Para encontrar o elemento com maior rank.
             * 
             */
            a = postAnswer_transversal(p, travel, a);

            bx = (Box)getSnd(a);

            if (bx)
                ll = (long)getP_id(bx->pid);
            else
                ll = -1;

            g_free(bx);
            g_free(a);
        }
        else
            ll = -1;

        return ll;
    }
    else
        return -1;
}

LONG_list questions_with_tag(TAD_community com, char *tag, Date begin, Date end)
{
    unsigned int n = 0, i, tag_code ;
    struct no *del, *ll = NULL;
    Record list;
    Record carrier;
    LONG_list rd;

    if (is_ON(com) && contains_tag(com,tag) )
    {   
        tag_code = code_tag(com, tag);
        list = createRecord(&ll, &n);
        carrier = createRecord(list, &tag_code);

        carrier = arraySeg_transversal(com, begin, end, collect_tag, carrier);

        /**
         * Carrier contêm já a lista ligada com os utilizadores com a indicada tag , ordenados.
         * */
        rd = create_list((int)n);
        /**
         * Conversão para os tipos dos professores.  
         * 
         **/
        
        for (i = 0; i < n; i++)
        {
            set_list(rd, i, ll->pid);
            del = ll;
            ll = ll->px;
            g_free(del);
        }

        g_free(list);
        g_free(carrier);
        return rd;
    }
    else
    {
        return NULL;
    }
}
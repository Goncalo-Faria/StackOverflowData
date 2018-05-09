
#include <glib.h>
#include <string.h>
#include <interface.h>
#include "Community.h"
#include <comondec.h>
#include <ctype.h>
#include <bArray.h>
#include <stdio.h>

//-------------------------------------------------------------------------------------
    // Da autoria de Gonçalo Faria && Guilherme Viveiros.
//-------------------------------------------------------------------------------------

// defines
#define inc_fst_long(x) set_fst_long(x, 1 + get_fst_long(x))
#define inc_snd_long(x) set_snd_long(x, 1 + get_snd_long(x))

// Métodos publicos.
STR_pair info_from_post(TAD_community com, long id);                               //#1
LONG_pair total_posts(TAD_community com, Date begin, Date end);                    //#3
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end);      //#6
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end); //#7
LONG_list contains_word(TAD_community com, char *word, int N);                     //#8

// Métodos privados.
static int match(void *value, void *user_data);
static void count(void *value, void *user_data);

//-------------------------------------------------------------------------------------

static int match(void *value, void *user_data)
{   
    /**
     * Esta função tenta encontrar uma palavra no titulo de uma publicação.
    */
    Record bx = (Record)user_data;
    Record cur = (Record)getSnd(bx);
    Record count = (Record)getFst(cur);
    char *title, *org, *word = (char *)getFst(bx);
    char *x;

    int lenz;
    LONG_list k = (LONG_list)getSnd(cur);
    int *index = (int *)getFst(count);
    int size = *(int *)getSnd(count);

    org = (char *)getP_name_point((Post)value);
    if (org)
    {
        /**
         * O titulo é processado por forma a  começar e acabar em espaço
         * assim como ser composto por letras minusculas apenas.
         * 
        */
        lenz = (strlen(org) + 3);
        title = g_malloc(sizeof(char) * lenz);

        *title = ' ';
        strcpy(title + 1, org);
        title[lenz - 1] = '\0';
        title[lenz - 2] = ' ';

        for (x = title; *x; x++)
           *x = tolower(*x);

        if ((getP_type((Post)value) == 1))
        {
            /**
             * É uma Pergunta.
            */

            if (strstr(title, word))
            {   
                /**
                 * Encontrou a palavra no título.
                 */
                set_list(k, *index, getP_id(value));
                *index += 1;
            }
        }

        g_free(title);
    }
    return (*index != size);
}

static void count(void *value, void *user_data)
{
    LONG_pair k = (LONG_pair)user_data;
    Post p = (Post)value;

    /**
     * Esta função caso a publicação seja uma pergunta incrementa a
     * variável que regista o numero de perguntas
     * caso seja resposta incrementa a variável que regista o numero de ocorrências de respostas.  
     * */

    if (getP_type(p) == 1)
        inc_fst_long(k); // é Questão.
    else
        inc_snd_long(k); // não Resposta.
}
//-------------------------------------------------------------------------------------

STR_pair info_from_post(TAD_community com, long id)
{
    unsigned char *str1, *str2;
    Util y = NULL;
    Post x = NULL;
    STR_pair result;
    unsigned long userid;
    if (is_ON(com))
    {   /**
        * Foi efetuado com sucesso a leitura dos ficheiro xml.
        */
        x = postSet_lookup(com, id);
        if (!x)
            return create_str_pair(NULL, NULL);
        /**
         * Acede ao conjunto das publicações.
         */

        if (getP_type(x) == 2)
        {
            /**
             * É uma resposta.
             */
            x = postSet_lookup(com, getP_parentId(x));
            /**
             * Acede à correspondente pergunta. 
             */
            if (!x)
                return create_str_pair(NULL, NULL);
        }
        str1 = getP_name(x);
        userid = getP_fund(x);

        y = userSet_id_lookup(com, userid);
        /**
         * Acede ao utilizador que criou a pergunta em questão. 
         */
        
        if (!y)
        {
            g_free(str1);
            return create_str_pair((char *)str1, NULL);
        }
        str2 = getU_name(y);
        result = create_str_pair((char *)str1, (char *)str2);

        g_free(str1);
        g_free(str2);
	
        return result;
    }
    else
        return NULL;
}

LONG_pair total_posts(TAD_community com, Date begin, Date end)
{   
    if (is_ON(com)){
        /**
        * Foi efetuado com sucesso a leitura dos ficheiro xml.
        */
       /**
        * É percorrido o bArray de publicação de begin até end
        * Aplciando count a todos os elementos nesse intervalo.
        */
        return (LONG_pair)arraySeg_transversal(com, begin, end, count, (void *)create_long_pair(0, 0));
    }else
        return NULL;
}

LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end)
{
    long i;
    LONG_list ll;
    Post newp;
    HEAP x; //
    if (is_ON(com))
    {
        /**
        * Foi efetuado com sucesso a leitura dos ficheiro xml.
        */

        /**
         * É criada uma fila de prioridade de prioridade numero de votos no processo de percorrer
         * o bArray de comunity.
         **/       
        x = arraySeg_Priority_Queue(com, begin, end, (unsigned long)N, votes_cmp, is_A, NULL);

        ll = create_list(N);

        /**
         * Conversão dos nossos tipos internos pelos esperados pela interrogação.
         */
        for (i = 0; i < N; i++)
        {
            if (!empty_H(x))
            {
                newp = (Post)rem_Heap(x);
                set_list(ll, N - 1 - i, (long)getP_id(newp));
            }
            else
            {
                set_list(ll, N - 1 - i, 0);
            }
        }

        destroy_H(x);
        return ll;
    }
    return NULL;
}

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end)
{
    long i;
    LONG_list ll;
    Post newp;
    HEAP x; //
    if (is_ON(com))
    {   
        /**
        * Foi efetuado com sucesso a leitura dos ficheiro xml.
        */
        x = arraySeg_Priority_Queue(com, begin, end, (unsigned long)N, nAns_cmp, is_Q, NULL);
        /**
         * É percorrida o bArray da publicação criada 
         * em begin até end. No processo é criada fila prioritária 
         * com prioridade numero de Respostas.
         **/
        ll = create_list(N);

        /**
         * Conversão do stipos interno para os tipos esperados na interrogação.
         */

        for (i = 0; i < N; i++)
        {
            if (!empty_H(x))
            {
                newp = (Post)rem_Heap(x);
                set_list(ll, N - 1 - i, (long)getP_id(newp));
            }
            else
            {
                set_list(ll, N - 1 - i, 0);
            }
        }

        destroy_H(x);
        return ll;
    }
    else
        return NULL;
}

LONG_list contains_word(TAD_community com, char *word, int N)
{
    int index = 0;
    int i;
    Record y, x;
    char *wordcpy;
    char *cur;
    LONG_list ll;
    if (is_ON(com))
    {   
        /**
        * Foi efetuado com sucesso a leitura dos ficheiro xml.
        */

        wordcpy = g_malloc(sizeof(char *) * (strlen(word) + 3));
        ll = create_list(N);
        
        sprintf(wordcpy, " %s ", word);
        //sprintf(wordcpy, "%s", word);
        /**
         *  A palavra a encontrar é processda.
         *  Todas as letras são convertidas para minusculas.
         *  São adicionados espaço no inicio e no fim desta. 
         */

        for (cur = wordcpy; *cur; cur++)
            *cur = tolower(*cur); 

        
        x = createRecord(wordcpy, createRecord(createRecord(&index, &N), ll));

        /**
         * É atravessado o array de forma cronologicamente inversa.
         * Esta para quando match, a função que é aplicada aos elementos,
         * devovler 1.
         * Match reune N publicações que contenham a palavra no título. 
         */
        //x = arrayRev_transversal(com, match, x);
        x = arrayRev_transversal(com,match,x);
        /**
         * Conversão para os tipso dos professores. 
         */
        if (index >= 0)
        {
            for (i = index; i < N; i++)
            { //caso não haja N match's.

                set_list(ll, i, 0);
            }
        }
        y = getSnd(x);

        g_free(getFst(y));
        g_free(y);
        g_free(x);
        g_free(wordcpy);
        return (ll);
    }
    else
        return NULL;
}

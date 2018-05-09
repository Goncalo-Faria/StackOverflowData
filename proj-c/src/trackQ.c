#include <glib.h>
#include <string.h>
#include <interface.h>
#include "Community.h"
#include "bArray.h"
#include <comondec.h>

//-------------------------------------------------------------------------------------
// Da autoria de Gonçalo Faria && Guilherme Viveiros.
//-------------------------------------------------------------------------------------

// Métodos publicos.
LONG_list top_most_active(TAD_community com, int N);                          //#2
USER get_user_info(TAD_community com, long id);                               //#5
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end); //#11

// Métodos privados.
static void get_active(void *key, void *value, void *user_data);
static void collect_top10(void *key, void *value, void *user_data);
static void gather_rep(void *key, void *value, void *user_data);
static void filter_hist(void *key, void *value, void *user_data);
static void fil_hash(void *b, void *user_data);
static int hist_tag(unsigned int tag, void *user_data);
static void *standart_make_pq(void (*freeCap)(void *), void *value, void *user_data, int (*Hcmp)(void *, void *, void *));

//-------------------------------------------------------------------------------------

static void gather_rep(void *key, void *value, void *user_data)
{
    /**
    * Esta função chama a standart_make_pq que é uma função genérica 
    * dedicada a tratar a criação de uma flia prioritária de prioridade a reputação de um utilziador 
    * enquanto se percorre uma estrutura. 
    **/
    user_data = standart_make_pq(NULL, value, user_data, rep_cmp);
}

static void collect_top10(void *key, void *value, void *user_data)
{
    /**
    * função executada na travessia da Bacia de atração que contem a colleção 
    * tanto de pergunta como respostas de um utilizador em questão.
    *  
    **/
    unsigned long *parent = (unsigned long *)key;
    unsigned long *child = (unsigned long *)value;
    unsigned long *used;
    int fund;
    long *id;
    Record rd, carrier, capsule = (Record)user_data;

    id = (long *)getFst(capsule);
    carrier = (Record)getSnd(capsule);
    rd = (Record)getFst(carrier);

    TAD_community com = (TAD_community)getSnd(carrier);

    Post pub;

    if (child)
    {
        // é uma resposta.
        used = child;

        /**
         *  - pequena execepção:
         *      . Devido à possibilidade do utilziar respoder a sua própria pergunta.
         * */

        pub = postSet_lookup(com, *parent);
        if (pub)
        { /*a pergunta existe em memória.*/
            fund = getP_fund(pub);

            if (fund == *id)
                rd = standart_make_pq(NULL, pub, rd, inv_post_compare);
        }
    }
    else
    {
        // é uma questão.
        used = parent;
    }

    pub = postSet_lookup(com, *used);

    if (pub) // se o post realmente existe no conjunto publicações.
        rd = standart_make_pq(NULL, pub, rd, inv_post_compare);
    /**
     * Chama standart_make_pq que é a função genérica 
    * dedicada a tratar a criação de uma flia prioritária de prioridade a data de criação de um post 
    * enquanto percorre uma estrutura.
    **/
}

static int hist_tag(unsigned int tid, void *user_data)
{
    /**
     * Função que é executada a cada elemento durante a travessia da lista de tags de um dado conjunto.
     * O objetivo é criar um histograma do uso de cada uma das tags.
     * 
    */
    int *c, tag = (int)tid;
    int *key;
    GHashTable *htable_tag = (GHashTable *)user_data;

    if (g_hash_table_contains(htable_tag, &tag))
    {
        /**
         * Se a tag se encontra no histogramam então o valor que regista o numero de
         * ocorrêncais desta é incrementado. 
        */
        c = g_hash_table_lookup(htable_tag, &tag);
        *c += 1;
    }
    else
    {
        /**
         * Se a tag não consta no histogram então é adicionada a este 
         * com a variável de ocorrências a registar 1.
        */
        c = g_malloc(sizeof(int));
        key = g_malloc(sizeof(unsigned int));

        *c = 1;
        *key = (int)tag;

        g_hash_table_insert(htable_tag, key, c);
    }

    return 1;
}

static void fil_hash(void *b, void *user_data)
{ /**
    * Esta função é executada a todas publicações que se encontram no bArray num determinado intervalo.
    * O objetivo é criar um histograma de uso tags.
    */
    Post p = (Post)b;
    unsigned long f = getP_fund(p);
    Record x = (Record)user_data;
    GHashTable *htable_usr = (GHashTable *)getFst(x);
    GHashTable *htable_tag = (GHashTable *)getSnd(x);

    if (g_hash_table_contains(htable_usr, &f))
    { /** 
        * Se o fundador desta publicação se encontra no top N dos utilizadores com maior reputação.
        * As tags desta são percorridas e contabilizadas no histograma.
        */
        htable_tag = postTag_transversal(p, hist_tag, htable_tag);
    }
}

static void filter_hist(void *key, void *value, void *user_data)
{
    /**
    * Esta função chama a standart_make_pq que é uma função genérica 
    * dedicada a tratar a criação de uma flia prioritária 
    * de prioridade o numero de ocorrencias de cada tag enquanto se percorre uma estrutura. 
    **/
    user_data = standart_make_pq(tag_count_free, createRecord(key, value), user_data, tag_count_cmp);
}

static void *standart_make_pq(void (*freeCap)(void *), void *value, void *user_data, int (*Hcmp)(void *, void *, void *))
{
    /**
     * Gene de um anamorfismo dedicado a criar um fila prioritária.
     * 
     * Esta função é aplicada a todos os elementos de uma estrutura
     * no processo de criação de uma fila prioritária ao percorrer uma qualquer estrutura.
     * 
     * 1) São adicionados N elementos ao bARray.
     * 2) Aplica-se o algoritmo de Floyd (heapify) no bArray para converter
     * este num fila de prioridade em 0(N).
     * 3) É testada a adesão na Heap aos restantes elementos da estrutura.
    */
    Record carrier = (Record)user_data;
    void *tmp, *rd = (void *)getFst(carrier);
    char *flag = (char *)getSnd(carrier);
    int sig = 0;
    bArray rd1;
    HEAP rd2;

    if (!*flag)
    { /**
        * A Heap ainda não foi criada.
        * O bArray ainda tem de ser preenchido.
        */
        rd1 = (bArray)rd;

        if (!is_full(rd1))
        { /**
            * O bArray não estám cheio. 
            */
            rd1 = add_to_A(rd1, value);
        }
        else
        { /**
            * O bArray está totalmente preenchido.
            * Correr heapify.
            * */
            rd2 = Generalized_Priority_Queue(rd1, length_A(rd1), Hcmp, yes, NULL);
            destroy_A(rd1);
            *flag = 1;

            tmp = get_root_point(rd2);
            rd2 = add_in_Place_H_signal(rd2, value, &sig);

            if (freeCap)
            {
                if (!sig)
                    freeCap(value);
                else
                    freeCap(tmp);
            }

            carrier = setFst(carrier, rd2);
        }
    }
    else
    { /** 
        * A Heap já foi criada e será efetuado o teste de adesão nesta do presente elemento. 
        * */

        rd2 = (HEAP)rd;

        tmp = get_root_point(rd2);
        rd2 = add_in_Place_H_signal(rd2, value, &sig);

        if (freeCap)
        {
            if (!sig)
                freeCap(value);
            else
                freeCap(tmp);
        }
    }
    return user_data;
}

static void get_active(void *key, void *value, void *user_data)
{
    /**
    * Esta função chama a standart_make_pq que é uma função genérica 
    * dedicada a tratar a criação de uma flia prioritária 
    * de prioridade numero de perguntas enquanto se percorre uma estrutura. 
    **/
    user_data = standart_make_pq(NULL, value, user_data, np_cmp);
}

//-------------------------------------------------------------------------------------

LONG_list top_most_active(TAD_community com, int N)
{
    int i, j;
    char flag;
    Record rd;
    LONG_list ll = NULL;
    Util c;
    HEAP hp;
    bArray extreme;
    if (is_ON(com))
    { /**
        * Foi efetuado com sucesso a leitura dos ficheiro xml.
        */
        flag = 0;
        rd = createRecord(init_A((unsigned long)N, NULL), &flag);
        /**
         * É percorrido o conjunto e aplicado get_active a todos os elementos.
         * */
        rd = userSet_id_transversal(com, get_active, (void *)rd);
        ll = create_list(N);
        //

        if (flag)
        {
            hp = (HEAP)getFst(rd);
        }
        else
        {
            /**
             * A fila prioritária não chegou a ser preenchida pois o bArray não alcançou os N elementos. 
             */
            extreme = (bArray)getFst(rd);
            hp = Generalized_Priority_Queue(extreme, length_A(extreme), np_cmp, yes, NULL);
            destroy_A(extreme);
        }

        j = length_H(hp);
        /**
         * É feita a conversão para os tipos do professor.
         */
        for (i = j - 1; i >= 0; i--)
        {
            c = rem_Heap(hp);
            set_list(ll, i, (long)getU_id(c));
        }

        for (i = j; i < N; i++)
            set_list(ll, i, 0);

        g_free(rd);
        destroy_H(hp);
    }
    return ll;
}

USER get_user_info(TAD_community com, long id)
{
    char flag;
    HEAP hp;
    bArray extreme;

    long post_history[10];
    char *short_bio = NULL;
    int i, j;

    Post the_post;
    USER send;
    Util x;
    Record rd, carrier, capsule;

    flag = 0;
    if (is_ON(com))
    {
        /**
        * Foi efetuado com sucesso a leitura dos ficheiro xml.
        */
        carrier = createRecord(createRecord((void *)init_A(10, NULL), (void *)&flag), (void *)com); // usar post compare.

        /**
         * Aceder ao utilizador com o id indicado.
         * */
        x = userSet_id_lookup(com, (unsigned long)id);

        if (!x)
        {
            /**
              * O Utilizador não existe.
            */
            g_free(getFst(carrier));
            g_free(carrier);
            return NULL;
        }

        capsule = createRecord(&id, carrier);

        short_bio = (char *)getU_bio(x);
        /**
         * Aplicar collect_top10 a todas as publciações que o utilizador criou. 
         * 
         */

        capsule = toBacia_transversal(x, collect_top10, capsule);

        carrier = (Record)getSnd(capsule);
        g_free(capsule);

        if (!flag)
        {
            /**
             * O bArray não chegou a ser completamente preenchido.
             * */
            rd = (Record)getFst(carrier);

            extreme = (bArray)getFst(rd);
            hp = Generalized_Priority_Queue(extreme, length_A(extreme), inv_post_compare, yes, NULL);
            destroy_A(extreme);
        }
        else
        {
            rd = (Record)getFst(carrier);
            hp = (HEAP)getFst(rd);
        }

        j = length_H(hp);
        /**
         * Conversão para os tipos dos professores.
         */
        for (i = j - 1; i >= 0; i--)
        { // vai do novo para o velho. (cronologia inversa)

            the_post = (Post)rem_Heap(hp);
            post_history[i] = (long)getP_id(the_post);
        }

        for (i = j; i < 10; i++)
            post_history[i] = 0;

        send = create_user(short_bio, post_history);

        g_free(short_bio);

        g_free(rd);
        g_free(carrier);

        destroy_H(hp);

        return send;
    }
    else
        return NULL;
}

LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end)
{
    HEAP hp;
    GHashTable *htable_usr, *htable_tag;
    Util cur;
    bArray extreme;
    Record rd;
    LONG_list ll;
    char flag;
    int i, j;
    int *code;

    if (is_ON(com))
    { /**
        * Foi efetuado com sucesso a leitura dos ficheiro xml.
        */
        flag = 0;

        /**
         * É aplicado gather_rep a todos os elementes do conjunto de utilizadores. 
         */
        rd = userSet_id_transversal(com, gather_rep, (void *)createRecord(init_A((unsigned long)N, NULL), &flag));

        /**
         * Criação de duas hashtables.
         * htable_tag para servir de histogram para a ocorrência de tags.
         * htable_usr para guardar o top N de utilizadores com maior reputação. 
         */
        htable_usr = g_hash_table_new_full(g_int64_hash, g_int64_equal, NULL, NULL);
        htable_tag = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, NULL);

        if (flag)
        {
            hp = (HEAP)getFst(rd);
        }
        else
        {
            /**
             *  Caso o bArray não tenha sido totalmente preenchido.
            */
            extreme = (bArray)getFst(rd);
            hp = Generalized_Priority_Queue(extreme, length_A(extreme), rep_cmp, yes, NULL);
            destroy_A(extreme);
        }
        g_free(rd);

        while (!empty_H(hp))
        { /**
            * Remover os N utilizadores com maior reputação e colocá-los na previamente referida
            * hashtable.
            * */
            cur = (Util)rem_Heap(hp);
            g_hash_table_insert(htable_usr, getU_id_point(cur), cur);
        }

        destroy_H(hp);
        /**
         * É percorrido o bArray de comunity que contem as publicações ordenadas cronologicamente
         * no intervalo de begin até end e a todas as publicaçôes é aplicada a função fil_hash.
         * */
        rd = arraySeg_transversal(com, begin, end, fil_hash, createRecord(htable_usr, htable_tag));

        htable_usr = (GHashTable *)getFst(rd);
        htable_tag = (GHashTable *)getSnd(rd);

        g_free(rd);
        g_hash_table_destroy(htable_usr);

        if (!g_hash_table_size(htable_tag))
        {
            g_hash_table_destroy(htable_tag);
            return NULL;
        }

        flag = 0;
        rd = createRecord(init_A(N, NULL), &flag);
        /**
         * Fazer uma fila prioritária com as N tags mais usadas, percorrendo
         * todas as tags no histograma e aplicando a função filter_hist
         * */
        g_hash_table_foreach(htable_tag, filter_hist, rd);
        if (flag)
        { // tudo na heap.
            hp = (HEAP)getFst(rd);
        }
        else
        {
            /**
             *  Caso o bArray não tenha sido totalmente preenchido.
            */

            extreme = (bArray)getFst(rd);
            hp = Generalized_Priority_Queue(extreme, length_A(extreme), tag_count_cmp, yes, NULL);
            destroy_A(extreme);
        }

        g_hash_table_destroy(htable_tag);
        g_free(rd);

        ll = create_list(N);

        j = length_H(hp);
        /**
         * Conversão para os tipos dos docentes.
        */
        for (i = j - 1; i >= 0; i--)
        {
            rd = (Record)rem_Heap(hp);
            code = (int *)getFst(rd);
            set_list(ll, i, (long)*code);
            tag_count_free(rd);
        }

        for (i = j; i < N; i++)
            set_list(ll, i, 0);
        destroy_H(hp);
        return ll;
    }
    else
        return NULL;
}
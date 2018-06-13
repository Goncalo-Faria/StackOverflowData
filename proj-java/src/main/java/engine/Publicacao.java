package engine;

import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collector;
import java.util.stream.Collectors;

public class Publicacao implements Comparable {
    private String id;
    private String nome;
    private int score;
    private int comment_count;
    private Set<Tag> tags;
    private LocalDate data;
    private String fundador;
    static private HashMap<String, Comparator<Publicacao>> comparadores;

    static {
        Publicacao.comparadores = new HashMap<String, Comparator<Publicacao>>();
        Publicacao.comparadores.put("MaisAntigo", new Comparator<Publicacao>() {
            public int compare(Publicacao x, Publicacao y) {
                return ((Publicacao) x).compareTo(y);
            }
        });
        Publicacao.comparadores.put("MaisRecente", Publicacao.comparadores.get("MaisAntigo").reversed());
        Publicacao.comparadores.put("MenorScore", new Comparator<Publicacao>() {
            public int compare(Publicacao x, Publicacao y) {
                Long val = Long.valueOf(x.getScore());
                return val.compareTo(Long.valueOf(y.getScore()));
            }
        });
        Publicacao.comparadores.put("MaiorScore", Publicacao.comparadores.get("MenorScore").reversed());

        Publicacao.comparadores.put("MenosRespostas", new Comparator<Publicacao>() {
            public int compare(Publicacao x, Publicacao y) {
                Pergunta l = (Pergunta) x, s = (Pergunta) y;
                Long val = Long.valueOf(l.getAnsCount());
                return val.compareTo(Long.valueOf(s.getAnsCount()));
            }
        });
        Publicacao.comparadores.put("MaisRespostas", Publicacao.comparadores.get("MenosRespostas").reversed());
    }

    static public Comparator<Publicacao> getComparator(String name) {
        return Publicacao.comparadores.get(name);
    }

    /**
     * Construtor parametrisado de Publicacao.
     */
    public Publicacao(LocalDate data, int sign) {
        if (sign < 0) {
            this.id = "0";
            this.fundador = "0";
        } else {
            this.id = "99999999999999";
            this.fundador = "99999999999999";
        }
        this.nome = "none";
        this.score = 0;
        this.comment_count = 0;

        this.tags = new HashSet<Tag>();
        this.data = data;

    }

    /**
     * Construtor parametrisado de Publicacao.
     */
    public Publicacao(String id, String nome, int score, int comment_count, LocalDate data, String fundador) {
        this.id = id;
        this.fundador = fundador;
        this.nome = nome;
        this.score = score;
        this.comment_count = comment_count;

        this.data = data;
        this.tags = new HashSet<Tag>();
    }

    /**
     * Construtor de cópia Publicacao.
     */
    public Publicacao(Publicacao x) {
        this.id = x.getId();
        this.fundador = x.getFundador();
        this.nome = x.getNome();
        this.score = x.getScore();
        this.comment_count = x.getComment_count();
        this.tags = x.getTags();
        this.data = x.getData();
    }

    // Getters!----------------------------------------------------------------------------------------------------------------
    /**
     * Obtêm o identifador.
     */
    public String getId() {
        return this.id;
    }

     /**
     * Obtêm o nome.
     */
    public String getNome() {
        return this.nome;
    }

     /**
     * Obtêm a Classificação.
     */
    public int getScore() {
        return this.score;
    }

     /**
     * Obtêm o número de comentários.
     */
    public int getComment_count() {
        return this.comment_count;
    }

     /**
     * Obtêm o conjunto de tags.
     */
    public Set<Tag> getTags() {
        return this.tags.stream().map(Tag::clone).collect(Collectors.toSet());
    }

     /**
     * Obtêm a data de criação.
     */
    public LocalDate getData() {
        return this.data;
    }

     /**
     * Obtêm o identifador do fundador.
     */
    public String getFundador() {
        return this.fundador;
    }

    // Setterss!-----------------------------------------------------------------------------------------------------------------
     /**
     * Atribui um identifador.
     */
    void setId(String x) {
        this.id = x;
    }

    /**
     * Atribui um nome.
     */
    void setNome(String x) {
        this.nome = x;
    }

    /**
     * Atribui uma classificão.
     */
    void setScore(int x) {
        this.score = x;
    }

    /**
     * Atribui um número de comentários.
     */
    void setComment_count(int x) {
        this.comment_count = x;
    }

    /**
     * Atribui o identifador do fundador.
     */
    public void setFundador(String pa) {
        this.fundador = pa;
    }

    /**
     * Adiciona uma tag.
     */
    public void addTag(Tag x) {
        if (!this.tags.contains(x))
            this.tags.add(x.clone());
    }

    /**
     * Atribui uma Data.
     */
    void setData(LocalDate x) {
        this.data = x;
    }

    /**
     * Verifica se é questão.
     */
    boolean isQuestion() {
        return (this instanceof Pergunta);
    }

    /**
     * Verifica se é reposta.
     */
    boolean isAnswer() {
        return (this instanceof Resposta);
    }

    // --------------------------------------------------------------------------------------------------------------------------
    /**
     * Faz uma cópia.
     */
    public Publicacao clone() {
        return new Publicacao(this);
    }

    /**
     * Verifica a igualdade de objetos.
     */
    public boolean equals(Object x) {
        if (x == this)
            return true;
        if (!(x instanceof Publicacao))
            return false;

        Publicacao y = (Publicacao) x;

        return ((y.getComment_count() == this.comment_count) && y.getData().equals(this.data)
                && y.getId().equals(this.id) && y.getNome().equals(this.nome) && (y.getScore() == this.getScore())
                && y.getTags().containsAll(this.tags));
    }

    /**
     * Ordem natural.
     */
    public int compareTo(Object x) {

        if (!(x instanceof Publicacao))
            return 0;

        Publicacao y = (Publicacao) x;
        int d = this.data.compareTo(y.getData());

        if ((this.id != null) && (y.getId() != null) && d == 0) {
            d = this.id.compareTo(y.getId());
        }
        return d;
    }
}

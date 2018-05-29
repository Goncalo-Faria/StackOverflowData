package engine;
import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collector;
import java.util.stream.Collectors;

public class Publicacao implements Comparable{
    private Long id;
    private String nome;
    private int score;
    private int comment_count;
    private int votes;
    private Set<engine.Tag> tags;
    private LocalDate data;
    private Long fundador;
    static private HashMap<String,Comparable<Publicacao>> comparadores;

    static {
        Publicacao.comparadores = new HashMap<String,Comparable<Publicacao>>();
        Publicacao.comparadores.put( ,new Comparator<Publicacao>() {
                    public int compare(Publicacao x, Publicacao y) {
                        return (-1) * x.comparePreco(y);
                    } });
        );
    }

    public Publicacao(){
        this.id = Long.valueOf(-1);
        this.fundador = Long.valueOf(-1);
        this.nome = "none";
        this.score = 0;
        this.comment_count = 0;
        this.votes = 0;
        this.tags = new HashSet<engine.Tag>();
        this.data = LocalDate.now();

    }

    public Publicacao(LocalDate data){
        this.id = Long.valueOf(-1);
        this.fundador = Long.valueOf(-1);
        this.nome = "none";
        this.score = 0;
        this.comment_count = 0;
        this.votes = 0;
        this.tags = new HashSet<engine.Tag>();
        this.data = data;

    }

    public Publicacao(String nome, Long id){
        this.id = id;
        this.fundador = Long.valueOf(-1);
        this.nome = nome;
        this.score = 0;
        this.comment_count = 0;
        this.votes = 0;
        this.tags = new HashSet<engine.Tag>();
        this.data = LocalDate.now();
    }

    public Publicacao(Long id , String nome , int score , int comment_count ,int votes , LocalDate data){
        this.id = id;
        this.fundador = Long.valueOf(-1);
        this.nome = nome;
        this.score = score;
        this.comment_count = comment_count;
        this.votes = votes;
        this.data = data;
        this.tags = new HashSet<engine.Tag>();
    }

    public Publicacao(Publicacao x){
        this.id = x.getId();
        this.fundador = x.getFundador();
        this.nome = x.getNome();
        this.score = x.getScore();
        this.comment_count = x.getComment_count();
        this.votes = x.getVotes();
        this.tags = x.getTags();
        this.data = x.getData();
    }

//Getters!----------------------------------------------------------------------------------------------------------------
    public Long getId(){return this.id;}

    public String getNome(){return this.nome;}

    public int getScore(){return this.score;}

    public int getComment_count(){return this.comment_count;}

    public int getVotes(){return this.votes;}

    public Set<engine.Tag> getTags(){return this.tags.stream().map(engine.Tag::clone).collect(Collectors.toSet());}

    public LocalDate getData(){return this.data;}

    public Long getFundador(){return this.fundador;}


//Setterss!-----------------------------------------------------------------------------------------------------------------
    void  setId(Long x){this.id = x;}

    void setNome(String x){this.nome =x;}

    void setScore(int x){this.score=x;}

    void setComment_count(int x){this.comment_count=x;}

    void setVotes(int x){this.votes = x;}

    void incUpVotes(){this.votes++;}

    void decDownVotes(){this.votes--;}

    public void setFundador(Long pa) {
        this.fundador = pa;
    }


    public void addTag(engine.Tag x){
        if(!this.tags.contains(x))
            this.tags.add(x.clone());
    }

    void setData(LocalDate x){this.data = x;}
    
    boolean isQuestion(){
        return (this instanceof engine.Pergunta);
    }

    boolean isAnswer(){
        return (this instanceof engine.Resposta);
    }

    //--------------------------------------------------------------------------------------------------------------------------
    public Publicacao clone(){
        return new Publicacao(this);
    }

    public boolean equals(Object x){
        if(x==this) return true;
        if(!(x instanceof Publicacao)) return false;

        Publicacao y = (Publicacao) x;

        return ((y.getComment_count() == this.comment_count) && y.getData().equals(this.data)
                 && y.getId().equals(this.id) && y.getNome().equals(this.nome) &&
                (y.getScore() == this.getScore()) && y.getTags().containsAll(this.tags) &&
                (y.getVotes() == this.votes) );
    }

    public int compareTo(Object x){

        if( !( x instanceof Publicacao)) return 0;

        Publicacao y = (Publicacao)x;
        if(this.data.isAfter(y.getData())) return -1;
        if(this.data.isBefore(y.getData())) return 1;
        return 0;
    }
}

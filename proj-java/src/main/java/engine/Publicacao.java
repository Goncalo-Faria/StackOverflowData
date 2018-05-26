import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collector;
import java.util.stream.Collectors;

public class Publicacao{
    Long id;
    String nome;
    int score;
    int comment_count;
    int votes;
    Set<Tag> tags;
    LocalDate data;

    public Publicacao(){
        this.id = Long.valueOf(-1);
        this.nome = "none";
        this.score = 0;
        this.comment_count = 0;
        this.votes = 0;
        this.tags = new HashSet<Tag>();
        this.data = LocalDate.now();
    }

    public Publicacao(String nome, Long id){
        this.id = id;
        this.nome = nome;
        this.score = 0;
        this.comment_count = 0;
        this.votes = 0;
        this.tags = new HashSet<Tag>();
        this.data = LocalDate.now();
    }

    public Publicacao(Long id , String nome , int score , int comment_count ,int votes , LocalDate data){
        this.id = id;
        this.nome = nome;
        this.score = score;
        this.comment_count = comment_count;
        this.votes = votes;
        this.data = data;
        this.tags = new HashSet<Tag>();
    }

    public Publicacao(Publicacao x){
        this.id = x.getId();
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

    public Set<Tag> getTags(){return this.tags.stream().map(Tag::clone).collect(Collectors.toSet());}

    public LocalDate getData(){return this.data;}

//Setterss!-----------------------------------------------------------------------------------------------------------------
    void  setId(Long x){this.id = x;}

    void setNome(String x){this.nome =x;}

    void setScore(int x){this.score=x;}

    void setComment_count(int x){this.comment_count=x;}

    void setVotes(int x){this.votes = x;}

    void incUpVotes(){this.votes++;}

    void decDownVotes(){this.votes--;}


    public void addTag(Tag x){
        if(!this.tags.contains(x))
            this.tags.add(x.clone());
    }

    void setData(LocalDate x){this.data = x;}
    
    boolean isQuestion(){
        return (this instanceof Pergunta);
    }

    boolean isAnswer(){
        return (this instanceof Resposta);
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

    public int compareTo(Publicacao x){
        if(this.data.isAfter(x.getData())) return 1;
        if(this.data.isBefore(x.getData())) return -1;
        return 0;
    }
}

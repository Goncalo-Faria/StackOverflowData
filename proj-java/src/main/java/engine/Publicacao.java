import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collector;
import java.util.stream.Collectors;

public class Publicacao{
    Long id;
    Long fundador;
    String nome;
    int score;
    int comment_count;
    int votes;
    char type;
    Set<Tag> tags;
    Set<Long> ans;
    LocalDate data;

    public Publicacao(){
        this.id =new Long(-1);
        this.fundador = new Long(-1);
        this.nome = "none";
        this.score = -1;
        this.comment_count = -1;
        this.votes = -1;
        this.type = ' ';
        this.tags = new HashSet<Tag>();
        this.ans = new HashSet<Long>();
        this.data = LocalDate.now();
    }

    public Publicacao(Long id , Long fundador , String nome , int score , int comment_count ,int votes , char type, LocalDate data){
        this.id = id;
        this.fundador = fundador;
        this.nome = nome;
        this.score = score;
        this.comment_count = comment_count;
        this.votes = votes;
        this.type = type;
        this.data = data;
        this.tags = new HashSet<Tag>();
        this.ans = new HashSet<Long>();
    }

    public Publicacao(Publicacao x){
        this.id = x.getId();
        this.fundador = x.getFundador();
        this.nome = x.getNome();
        this.score = x.getScore();
        this.comment_count = x.getComment_count();
        this.votes = x.getVotes();
        this.type = x.getType();
        this.tags = x.getTags();
        this.ans = x.getAns();
        this.data = x.getData();
    }

//Getters!----------------------------------------------------------------------------------------------------------------
    public Long getId(){return this.id;}

    public Long getFundador(){return this.fundador;}

    public String getNome(){return this.nome;}

    public int getScore(){return this.score;}

    public int getComment_count(){return this.comment_count;}

    public int getVotes(){return this.votes;}

    public char getType(){return this.type;}

    public Set<Tag> getTags(){return this.tags.stream().map(Tag::clone).collect(Collectors.toSet());}

    public Set<Long> getAns(){return (new TreeSet<Long>(this.ans));}

    public LocalDate getData(){return this.data;}

//Setterss!-----------------------------------------------------------------------------------------------------------------
    void  setId(Long x){this.id = x;}

    void setFundador(Long x){this.fundador = x;}

    void setNome(String x){this.nome =x;}

    void setScore(int x){this.score=x;}

    void setComment_count(int x){this.comment_count=x;}

    void setVotes(int x){this.votes = x;}

    void incUpVotes(){this.votes++;}

    void decDownVotes(){this.votes--;}

    void setQuestion(){this.type ='Q';}

    void setAnswer(){this.type ='A';}

    public void addAnswer(Long x){
        this.ans.add(x);
    }

    public void addTag(Tag x){
        if(!this.tags.contains(x))
            this.tags.add(x.clone());
    }

    void setData(LocalDate x){this.data = x;}
    
    boolean isQuestion(){
        return (this.type=='Q');
    }

    boolean isAnswer(){
        return (this.type=='A');
    }

    //--------------------------------------------------------------------------------------------------------------------------
    public Publicacao clone(){
        return new Publicacao(this);
    }

    public boolean equals(Object x){
        if(x==this) return true;
        if(x.getClass() != getClass() || x == null) return false;

        Publicacao y = (Publicacao) x;

        return (y.getAns().containsAll(this.ans) && (y.getComment_count() == this.comment_count) && y.getData().equals(this.data) &&
                y.getFundador().equals(this.fundador) && y.getId().equals(this.id) && y.getNome().equals(this.nome) &&
                (y.getScore() == this.getScore()) && y.getTags().containsAll(this.tags) && (y.getType() == this.type) &&
                (y.getVotes() == this.votes) );
    }

    public int compareTo(Publicacao x){
        if(this.data.isAfter(x.getData())) return 1;
        if(this.data.isBefore(x.getData())) return -1;
        return 0;
    }
}

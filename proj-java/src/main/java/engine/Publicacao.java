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
    Map<Long,Tag> tags;
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
        this.tags = new HashMap<Long,Tag>();
        this.ans = new HashSet<Long>();
        this.data = LocalDate.now();
    }

    public Publicacao(Long id , Long fundador , String nome , int score , int comment_count ,int votes , char type , Map<Long,Tag> tags , Set<Long> ans , LocalDate data){
        this.id = id;
        this.fundador = fundador;
        this.nome = nome;
        this.score = score;
        this.comment_count = comment_count;
        this.votes = votes;
        this.type = type;
        setTags(tags);
        setAns(ans);
        this.data = data;
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
    public long getId(){return this.id;}

    public long getFundador(){return this.fundador;}

    public String getNome(){return this.nome;}

    public int getScore(){return this.score;}

    public int getComment_count(){return this.comment_count;}

    public int getVotes(){return this.votes;}

    public char getType(){return this.type;}

    public Map<Long,Tag> getTags(){return this.tags.entrySet().stream().collect(Collectors.toMap(l->l.getKey(), l->l.getValue().clone()));}

    public Set<Long> getAns(){return this.ans.stream().collect(Collectors.toSet());}

    public LocalDate getData(){return this.data;}

//Setterss!-----------------------------------------------------------------------------------------------------------------
    void  setId(long x){this.id = x;}

    void setFundador(long x){this.fundador = x;}

    void setNome(String x){this.nome =x;}

    void setScore(int x){this.score=x;}

    void setComment_count(int x){this.comment_count=x;}

    void setVotes(int x){this.votes = x;}

    void setUpVotes(){this.votes++;}

    void setDownVotes(){this.votes--;}

    void setType(char x){this.type =x;}

    void setTags(Map<Long,Tag> x){this.tags = x.entrySet().stream().collect(Collectors.toMap(l->l.getKey(), l->l.getValue().clone()));}

    void setAns(Set<Long> x){this.ans = x.stream().collect(Collectors.toSet());}

    void setData(LocalDate x){this.data = x;}

    //--------------------------------------------------------------------------------------------------------------------------
    public Publicacao clone(){
        return new Publicacao(this);
    }

    public boolean equals(Object x){
        if(x==this) return true;
        if(x.getClass() != getClass() || x == null) return false;

        Publicacao y = (Publicacao) x;

        return (y.getAns().equals(this.getAns()) && y.getComment_count() == this.getComment_count() && y.getData().equals(this.getData()) &&
                y.getFundador() == this.getFundador() && y.getId() == this.getId() && y.getNome().equals(this.getNome()) &&
                y.getScore() == this.getScore() && y.getTags().equals(this.getTags()) && y.getType() == this.getType() &&
                y.getVotes() == this.getVotes());
    }
    
    public int compareData(Publicacao x){
        if(this.data.isAfter(x.getData())) return 1;//quando a data principal for > que a data de x
        if(this.data.isBefore(x.getData())) return -1;//quando a data principal for < que a data de x
        return 0; //quando as datas forem iguais
    }

    public void addAns(Long x){
        this.ans.add(x);
    }
    public boolean addTags(Tag x){
        if(this.tags.get(x.getId())) return false;
        this.tags.put(x.getId(), x.clone());
    }
}

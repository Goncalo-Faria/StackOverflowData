import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collector;
import java.util.stream.Collectors;


public class Utilizador{

    Long id;
    String nome;
    int Q;
    int A;
    String bio;
    Map<Long,Set<Long>> bacia;
    int rep;

    public Utilizador(){
        this.id = Long.valueOf(-1);
        this.nome = "nenhum";
        this.Q = 0;
        this.A = 0;
        this.bio = "nenhum";
        this.bacia = new HashMap<Long,Set<Long>>();
        this.rep = 0;
    }


    public Utilizador(Long id, String nome){
        this.id = id;
        this.nome = nome;
        this.Q = 0;
        this.A = 0;
        this.bio = "nenhum";
        this.bacia = new HashMap<Long,Set<Long>>();
        this.rep = 0;
    }

    public Utilizador(Long id , String nome, int Q , int A, String bio, HashMap<Long,Set<Long>> x, int rep){
        this.id = id;
        this.nome = nome;
        this.Q = Q;
        this.A = A;
        this.bio = bio;
        this.setBacia(x);
        this.rep = rep;
    }

    public Utilizador(Long id , String nome, int Q , int A, String bio, int rep){
        this.id = id;
        this.nome = nome;
        this.Q = Q;
        this.A = A;
        this.bio = bio;
        this.bacia = new HashMap<Long,Set<Long>>();
        this.rep = rep;
    }

    public Utilizador(Utilizador x){
        this.id = x.getId();
        this.nome = x.getNome();
        this.Q = x.getQ();
        this.A = x.getA();
        this.bio = x.getBio();
        this.bacia = x.getBacia();
        this.rep = x.getRep();
    }
    
//Getters!----------------------------------------------------------------------------------------------------------------
    public Long getId(){return this.id;}

    public String getNome(){return this.nome;}

    public int getQ(){return this.Q;}

    public int getA(){return this.A;}

    public String getBio(){return this.bio;}

    public Set<Long> getBacia(){return this.bacia.stream().collect(Collectors.toSet());}

    public int getRep(){return this.rep;}

//Setters!----------------------------------------------------------------------------------------------------------------
    public void setId(Long x){this.id = x;}

    public void setNome(String x){this.nome = x;}

    public void setQ(int x){this.Q = x;}

    public void setA(int x){this.A = x;}

    public void setBio(String x){this.bio = x;}

    public void setBacia(Set<Long> x){this.bacia = x.stream().collect(Collectors.toSet());}

    public void setRep(int x){this.rep = x;}

//-------------------------------------------------------------------------------------------------------------------------
    public Utilizador clone(){
        return new Utilizador(this);
    }

    public boolean equals(Object x){
        if(x == this) return true;
        if(x.getClass() != getClass() || x == null) return false;
        Utilizador y = (Utilizador) x;
        
        return (y.getA() == (this.getA()) && y.getBacia().equals(this.getBacia()) &&
        y.getBio().equals(this.getBio()) && y.getId() == this.getId() && y.getNome() == this.getNome()
        && y.getQ()==(this.getQ()) && y.getRep()== (this.getRep()));
    }

    public void addBacia(Long x){
        this.bacia.add(x);
    }
    

}


package engine;
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

    public Map<Long,Set<Long>> getBacia(){return this.bacia.entrySet().stream().collect(Collectors.toMap( l -> l.getKey(), l-> new HashSet<Long>(l.getValue())));}

    public int getRep(){return this.rep;}

//Setters!----------------------------------------------------------------------------------------------------------------
    public void setId(Long x){this.id = x;}

    public void setNome(String x){this.nome = x;}

    public void setQ(int x){this.Q = x;}

    public void incQ(){this.Q++;}

    public void setA(int x){this.A = x;}

    public void incA(){this.A++;}

    public void setBio(String x){this.bio = x;}

    public void setBacia(Map<Long,Set<Long>> x){this.bacia = x.entrySet().stream().collect(Collectors.toMap( l -> l.getKey(), l-> new HashSet<Long>(l.getValue())));}

    public void addBacia(engine.Publicacao x){
        if(x instanceof engine.Resposta){
            engine.Resposta y = (engine.Resposta) x;
            Long fund = y.getFundador();

            if( this.bacia.containsKey(fund)){
                /* já está introduzida pergunta*/
                Set<Long> ans = this.bacia.get(fund);
                if( !ans.contains(y.getId()) ){
                    ans.add(y.getId());
                }

            }else{
                Set<Long> ans = new HashSet<Long>();
                ans.add(getId());
                this.bacia.put(y.getFundador(),ans);
            }

        }

        if(x instanceof engine.Pergunta){
            if(this.bacia.containsKey(x.getId())){
                Set<Long> ans = this.bacia.get(x.getId());
                if(!ans.contains(x.getId()))
                    ans.add(x.getId());

            }else{
                Set<Long> ans = new HashSet<Long>();
                ans.add(getId());
                this.bacia.put(x.getId(),ans);
            }
        }
    }

    public void setRep(int x){this.rep = x;}

//-------------------------------------------------------------------------------------------------------------------------
    public Utilizador clone(){
        return new Utilizador(this);
    }

    public boolean equals(Object x){
        if(x == this) return true;
        if(!(x instanceof Utilizador)) return false;
        Utilizador y = (Utilizador) x;
        
        return (y.getA() == (this.A) && y.getBacia().keySet().containsAll(this.bacia.keySet()) &&
            y.getBio().equals(this.bio) && y.getId().equals(this.id) && y.getNome().equals(this.nome)
                && (y.getQ()==this.Q) && (y.getRep() == this.rep));
    }

//-------------------------------------------------------------------------------------------------------------------------

    public Set<Long> mutualIntervention(Utilizador x){
        /* Calcula interseção*/
        Set<Long> tmp = x.getBacia().keySet();
        final Set<Long> small,big;

        if( tmp.size() >= this.bacia.size() ){
            small = this.bacia.keySet();
            big = tmp;
        }else{
            small = tmp;
            big   = this.bacia.keySet();
        }

        return small.stream().filter(l -> big.contains(l) ).collect(Collectors.toSet());

    }


}


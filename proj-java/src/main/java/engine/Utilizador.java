package engine;
import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collector;
import java.util.stream.Collectors;


public class Utilizador{

    private String id;
    private String nome;
    private int Q;
    private int A;
    private String bio;
    private Map<String,Set<String>> bacia;
    private int rep;
    static private HashMap<String,Comparator<Utilizador>> comparadores;

    static {
        Utilizador.comparadores = new HashMap<String,Comparator<Utilizador>>();
        Comparator<Utilizador> utilAti = new Comparator<Utilizador>() {
            public int compare(Utilizador x, Utilizador y) {
                Long val = Long.valueOf(y.getQ()+ y.getA());
                return val.compareTo(Long.valueOf(x.getQ() + x.getA()));
            } };

        Utilizador.comparadores.put("UtilizadoresAtivos",utilAti );

        Utilizador.comparadores.put("MaiorReputacao",
                new Comparator<Utilizador>() {
                    public int compare(Utilizador x, Utilizador y) {
                        Long val = Long.valueOf(y.getRep());
                        return val.compareTo(Long.valueOf(x.getRep()));
                    } });
    }

    static public Comparator<Utilizador> getComparator(String name){
        return Utilizador.comparadores.get(name);
    }

    public Utilizador(String id , String nome, int Q , int A, String bio, int rep){
        this.id = id;
        this.nome = nome;
        this.Q = Q;
        this.A = A;
        this.bio = bio;
        this.bacia = new HashMap<String,Set<String>>();
        this.rep = rep;
    }

    public Utilizador(Utilizador x){
        this.id = x.getId();
        try{
            this.nome = x.getNome();
        }catch( NullPointerException ex){
            this.nome = null;
        }
        this.Q = x.getQ();
        this.A = x.getA();
        this.bio = x.getBio();
        this.bacia = x.getBacia();
        this.rep = x.getRep();
    }
    
//Getters!----------------------------------------------------------------------------------------------------------------
    public String getId(){return this.id;}

    public String getNome() throws NullPointerException {if(this.nome==null) new NullPointerException( this.id + " Não contêm título");return this.nome;}

    public int getQ(){return this.Q;}

    public int getA(){return this.A;}

    public String getBio(){return this.bio;}

    public Map<String,Set<String>> getBacia(){return this.bacia.entrySet().stream().collect(Collectors.toMap( l -> l.getKey(), l-> new HashSet<String>(l.getValue())));}

    public int getRep(){return this.rep;}

//Setters!----------------------------------------------------------------------------------------------------------------
    public void setId(String x){this.id = x;}

    public void setNome(String x){this.nome = x;}

    public void setQ(int x){this.Q = x;}

    public void incQ(){this.Q++;}

    public void setA(int x){this.A = x;}

    public void incA(){this.A++;}

    public void setBio(String x){this.bio = x;}

    public void setBacia(Map<String,Set<String>> x){this.bacia = x.entrySet().stream().collect(Collectors.toMap( l -> l.getKey(), l-> new HashSet<String>(l.getValue())));}

    public void addBacia(Publicacao x) {

        if ( x.getFundador().equals( this.id ) ){

            if (x.isAnswer()) {
                Resposta y = (Resposta) x;
                String parentpost = y.getParentId();

                if (this.bacia.containsKey(parentpost)) {
                    /* já está introduzida pergunta*/
                    Set<String> ans = this.bacia.get(parentpost);
                    if (!ans.contains(y.getId())) {
                        ans.add(y.getId());
                        this.incA();
                    }

                } else {
                    Set<String> ans = new HashSet<String>();
                    ans.add(y.getId());
                    this.bacia.put(parentpost, ans);
                    this.incA();
                }

            }

            if (x.isQuestion()) {
                if (this.bacia.containsKey(x.getId())) {
                    Set<String> ans = this.bacia.get(x.getId());
                    if (!ans.contains(x.getId())) {
                        ans.add(x.getId());
                        this.incQ();
                    }
                } else {
                    Set<String> ans = new HashSet<String>();
                    ans.add(x.getId());
                    this.bacia.put(x.getId(), ans);
                    this.incQ();
                }
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
        boolean name;
        try{
            name = y.getNome().equals(this.nome);
        }catch( NullPointerException ex){
            name = (this.nome==null);
        }
        return (y.getA() == (this.A) && y.getBacia().keySet().containsAll(this.bacia.keySet()) &&
            y.getBio().equals(this.bio) && y.getId().equals(this.id) && name
                && (y.getQ()==this.Q) && (y.getRep() == this.rep));
    }

//-------------------------------------------------------------------------------------------------------------------------

    public Set<String> mutualIntervention(Utilizador x){
        /* Calcula interseção*/
        Set<String> tmp = x.getBacia().keySet();
        final Set<String> small,big;

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


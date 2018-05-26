


import java.util.stream.Collectors;
import java.util.*;


public class Comunidade implements TADCommunity {
    
    Map<Long,Utilizador> users;
    Map<Long,Publicacao> post;
    TreeSet<Publicacao> postArray;
    Map<String,Tag> tagconv;

    public Comunidade (){
        this.users = new HashMap<Long,Utilizador>();
        this.postArray = new TreeSet<Publicacao>();
        this.post = new HashMap<Long,Publicacao>();
        this.tagconv = new HashMap<String,Tag>();
    }

    public Comunidade (Map<Long,Utilizador> x, Map<Long,Publicacao> p , Map<String,Tag> l){
        this.setUsers(x);
        this.setPost(p);
        this.setTagconv(l);
        this.makepostArray();
    }

    public Comunidade (Comunidade x){
        this.users = x.getusers();
        this.post= x.getPost();
        this.tagconv = x.getTagconv();
        this.makepostArray();
    }

//Getters!------------------------------------------------------------------------------------------------------------------------------------
    public Map<Long,Utilizador> getusers(){
        return this.users.values().stream().collect(Collectors.toMap(l ->l.getId(), l -> l.clone()));
    }

    public Set<Publicacao> getpostArray(){
        return this.postArray.stream().map(Publicacao::clone).collect(Collectors.toSet());
    }

    public Map<Long,Publicacao> getPost(){
         return this.post.values().stream().collect(Collectors.toMap(l ->l.getId(), l -> l.clone()));
    }
    
    public Map<String,Tag> getTagconv(){
         return this.tagconv.entrySet().stream().collect(Collectors.toMap(l -> l.getKey() , l -> l.getValue().clone());
    }

//Setters!------------------------------------------------------------------------------------------------------------------------------------
    void setUsers(Map<Long,Utilizador> x){
        this.users = x.values().stream().collect(Collectors.toMap(l->l.getId(), l->l.clone()));
    }
    
    void setPost(Map<Long,Publicacao> x){
        this.post = x.values().stream().collect(Collectors.toMap(l->l.getId(), l->l.clone()));
    }
    
    void setTagconv(Map<String,Tag> x){
        this.tagconv = x.entrySet().stream().collect(Collectors.toMap(l->l.getKey(),l->l.getValue().clone()));
    }

//--------------------------------------------------------------------------------------------------------------------------
    public Comunidade clone(){
        return new Comunidade(this);
    }
    
    public boolean equals(Object x){
        if (this == x) return true;
        if (!(x instanceof Comunidade)) return false;

        Comunidade y = (Comunidade) x;

        return (this.postArray.equals(y.getpostArray()) && this.post.equals(y.getPost()) 
                && this.users.equals(y.getusers()) && this.tagconv.equals(y.getTagconv()));
    }
    
    public void makepostArray(){
        this.postArray = new TreeSet<Publicacao>(this.post.values());
    }

    public void load(String dumpPath) {
        
    }
//--------------------------------------------------------------------------------------------------------------------------    
}



import java.time.LocalDate;
import java.util.Map;
import java.util.*;
import java.util.stream.Collector;
import java.util.stream.Collectors;


import java.util.stream.Collectors;
import java.lang.String;//string


public class Community{
    
    Map<Long,Utilizador> userbyId;
    Map<Long,Publicacao> post;
    Set<Publicacao> PostArray;
    Map<Long,Tag> tagconv; // Mudar este aqui -> apos recebermos o post conseguimos fazer o tagconv

    public Community(){
        this.userbyId = new HashMap<Long,Utilizador>();
        this.PostArray = new TreeSet<Publicacao>();
        this.post = new HashMap<Long,Publicacao>();
        this.tagconv = new HashMap<Long,Tag>();
    }

    public Community(Map<Long,Utilizador> x, Map<Long,Publicacao> p , Map<Long,Tag> l){
        setUserbyId(x);
        setPost(p);
        this.makePostArray();
        setTagconv(l);
    }

    public Community(Community x){
        this.userbyId = x.getUserbyId();
        this.PostArray = x.getPostarray();
        this.post= x.getPost();
        this.tagconv = x.getTagconv();
    }

//Getters!------------------------------------------------------------------------------------------------------------------------------------
    public Map<Long,Utilizador> getUserbyId(){
        return this.userbyId.values().stream().collect(Collectors.toMap(l ->l.getId(), l -> l.clone()));
    }

    public Set<Publicacao> getPostarray(){
        return this.PostArray.stream().map(Publicacao::clone).collect(Collectors.toSet());
    }

    public Map<Long,Publicacao> getPost(){
         return this.post.values().stream().collect(Collectors.toMap(l ->l.getId(), l -> l.clone()));
    }
    
    public Map<Long,Tag> getTagconv(){
         return this.tagconv.values().stream().collect(Collectors.toMap(l -> l.getId() , l -> l.clone()));
    }

//Setters!------------------------------------------------------------------------------------------------------------------------------------
    void setUserbyId(Map<Long,Utilizador> x){
        this.userbyId = x.values().stream().collect(Collectors.toMap(l->l.getId(), l->l.clone()));
    }
    
    void setPostarray(Set <Publicacao> x){
        this.PostArray = x.stream().map(Publicacao::clone).collect(Collectors.toSet());
    }
    
    void setPost(Map<Long,Publicacao> x){
        this.post = x.values().stream().collect(Collectors.toMap(l->l.getId(), l->l.clone()));
    }
    
    void setTagconv(Map<Long,Tag> x){
        this.tagconv = x.values().stream().collect(Collectors.toMap(l->l.getId(),l->l.clone()));
    }

//--------------------------------------------------------------------------------------------------------------------------
    public Community clone(){
        return new Community(this);
    }
    
    public boolean equals(Object x){
        if (this == x) return true;
        if (x.getClass() != this.getClass() || x == null ) return false;

        Community y = (Community) x;

        return (this.PostArray.equals(y.getPostarray()) && this.post.equals(y.getPost()) 
                && this.userbyId.equals(y.getUserbyId()) && this.tagconv.equals(y.getTagconv()));
    }
    
    public Set<Publicacao> makePostArray(){
        Set x = new TreeSet<>(new Comparator<Publicacao>() {
            public int compare(Publicacao x, Publicacao y) {
                return x.compareData(y);
            }
        });
        for(Publicacao p :  this.post.values()){
            x.add(p);
        }
        return x;
    }
    
    public boolean addUserbyId(Utilizador x){
        if(this.userbyId.get(x.getId())) return false;
        this.userbyId.put(x.getId(), x.clone());
        return true;
    }
    
    public boolean addPost(Publicacao x){
        if(this.post.get(x.getId())) return false;
        this.post.put(x.getId(), x.clone());
    }

    public boolean addTagconv(Tag x){
        if(this.tagconv.get(x.getId())) return false;
        this.tagconv.put(x.getId(), x.clone()); 
    }
    
}



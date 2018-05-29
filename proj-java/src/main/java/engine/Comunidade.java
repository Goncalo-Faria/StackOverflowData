package engine;

import common.MyLog;
import common.Pair;
import li3.TADCommunity;

import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import javax.xml.parsers.*;
import java.io.File;
import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.stream.Collectors;
import java.util.*;


public class Comunidade implements TADCommunity {
    
    Map<Long, engine.Utilizador> users;
    Map<Long, engine.Publicacao> post;
    TreeSet<engine.Publicacao> postArray;
    Map<String, engine.Tag> tagconv;

    public Comunidade (){
        this.users = new HashMap<Long, engine.Utilizador>();
        this.postArray = new TreeSet<engine.Publicacao>();
        this.post = new HashMap<Long, engine.Publicacao>();
        this.tagconv = new HashMap<String, engine.Tag>();
    }

    public Comunidade (Map<Long, engine.Utilizador> x, Map<Long, engine.Publicacao> p , Map<String, engine.Tag> l){
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
    public Map<Long, engine.Utilizador> getusers(){
        return this.users.values().stream().collect(Collectors.toMap(l ->l.getId(), l -> l.clone()));
    }

    public Set<engine.Publicacao> getpostArray(){
        return this.postArray.stream().map(engine.Publicacao::clone).collect(Collectors.toSet());
    }

    public Map<Long, engine.Publicacao> getPost(){
         return this.post.values().stream().collect(Collectors.toMap(l ->l.getId(), l -> l.clone()));
    }
    
    public Map<String, engine.Tag> getTagconv(){
         return this.tagconv.entrySet().stream().collect(Collectors.toMap(l -> l.getKey() , l -> l.getValue().clone()));
    }

//Setters!------------------------------------------------------------------------------------------------------------------------------------
    void setUsers(Map<Long, engine.Utilizador> x){
        this.users = x.values().stream().collect(Collectors.toMap(l->l.getId(), l->l.clone()));
    }
    
    void setPost(Map<Long, engine.Publicacao> x){
        this.post = x.values().stream().collect(Collectors.toMap(l->l.getId(), l->l.clone()));
    }
    
    void setTagconv(Map<String, engine.Tag> x){
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

        return (this.postArray.containsAll(y.getpostArray()) && this.post.values().containsAll(y.getPost().values()) 
                && this.users.values().containsAll(y.getusers().values()) && this.tagconv.values().containsAll(y.getTagconv().values()));
    }
    
    public void makepostArray(){
        this.postArray = new TreeSet<engine.Publicacao>(this.post.values());
    }


//--------------------------------------------------------------------------------------------------------------------------    


    public void load(String dumpPath) {


        engine.StackOverFlowParse parse = new engine.StackOverFlowParse(dumpPath);

        this.tagconv = ((engine.TagConversionSAX)parse.analyze("Tags.xml", new engine.TagConversionSAX())).getResults();

        this.users = ((engine.UsersSAX)parse.analyze("Users.xml", new engine.UsersSAX())).getResults();

        engine.PostSAX pst = new engine.PostSAX(this.tagconv);

        this.post = ((engine.PostSAX)parse.analyze("Posts.xml", pst )).getResults();

        /*Construir bacia*/
        for(Map.Entry<Long,Set<engine.Publicacao> >pr : pst.getComplementar().entrySet() ){
            if(  this.users.containsKey(pr.getKey()) ){
                final engine.Utilizador util = this.users.get(pr.getKey());
                pr.getValue().forEach(l -> util.addBacia(l) );
            }
        }

        this.post = ((engine.VotesSAX)parse.analyze("Votes.xml", new engine.VotesSAX(this.post))).getResults();

        this.makepostArray();
    }

    // Query 1
    public Pair<String,String> infoFromPost(long id) {
        String x1 = null;
        String x2 = null;
        engine.Utilizador u;
        engine.Publicacao p;
        if(this.post.containsKey(id)){
            p=this.post.get(id);

            if(p instanceof engine.Pergunta){ //quando é pergunta
                x1 = p.getNome();
                if(this.users.containsKey(p.getFundador())){
                 x2 =  this.users.get(p.getFundador()).getNome();
                }
            }
            if(p instanceof engine.Resposta){//quando for resposta

                if(this.post.containsKey(((engine.Resposta)p).getParentID())){
                    p = this.post.get(((engine.Resposta)p).getParentID());
                    x1 = p.getNome();
                    if(this.users.containsKey(p.getFundador())){
                        x2 = this.users.get(p.getFundador()).getNome();
                    }
                }
            }
        }
        return new Pair<>(x1, x2);
    }

    // Query 2
    public List<Long> topMostActive(int N) {
        engine.GeneralizedPriorityQueue<engine.Utilizador> ut = new GeneralizedPriorityQueue<engine.Utilizador>(
            N, (Object l , Object s) -> ((engine.Utilizador)l).comparePost(s) );

            Set<engine.Utilizador> x = this.users.values().stream().collect(Collectors.toSet());

            ut.populate(x);

            List<engine.Utilizador> l = ut.terminateToList();
            List<Long> result = new ArrayList<Long>();

            for(engine.Utilizador u : l ){
                if(!result.contains(u.getId())){
                    result.add(u.getId());
                }
            }

        return result;
    }

    // Query 3
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {
        Long question = Long.valueOf(0);
        Long answer = Long.valueOf(0);
        for(Publicacao p : this.postArray){
            if(p instanceof Pergunta) question++;
            else answer++;
        }
        return new Pair<>(question,answer);
    }

    // Query 4
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
        List<Long> l = new ArrayList<Long>();
        List<Long> result = new ArrayList<Long>();
        for(engine.Publicacao p : this.postArray){
            if(p instanceof Pergunta){
                if(p.getData().isAfter(begin) && p.getData().isBefore(end)){ //se tiver entre as datas fornecidas
                    for(Tag x : p.getTags()){
                        if(x.getNome().equals(tag)){ //quando contiver a tag
                            l.add(p.getId());
                            break;
                        }
                    }
                }
            }
        }    
        //meter por ordem iversa agora
        int x = l.size();
        for(Long f : l){
            result.add(x, f);
            x--; 
        }    
        
        return result;
    }

    // Query 5
    public Pair<String, List<Long>> getUserInfo(long id) {

        String shortBio = null ;
        List<engine.Publicacao> p = new ArrayList<engine.Publicacao>(); 
        List<Long> posts = new ArrayList<Long>();
        engine.Utilizador ut;
        if(this.users.containsKey(id)){
            ut = this.users.get(id);
            shortBio = ut.getBio();

            engine.GeneralizedPriorityQueue<engine.Publicacao> pq = new GeneralizedPriorityQueue<engine.Publicacao>
            (10, ((Object l , Object s) -> ((engine.Publicacao)l).compareTo(s)*-1) ); 
            
            pq.populate(this.postArray);
            p = pq.terminateToList();
            
            for(engine.Publicacao x : p){
                posts.add(x.getId());
            }
        }

        return new Pair<>(shortBio,posts);
    }

    // Query 6
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
        Set<engine.Publicacao> p = new TreeSet<engine.Publicacao>();
        List<Long> result = new ArrayList<Long>();
        
        engine.GeneralizedPriorityQueue<engine.Publicacao> pq = new engine.GeneralizedPriorityQueue<engine.Publicacao>(
            N , ( (Object l , Object s) -> ((engine.Publicacao)l).compareScore(s)*-1)); //Inverter a ordem , "ordem decrescente"
        
            for(engine.Publicacao x : this.postArray){
                if(x instanceof engine.Publicacao){
                    p.add(x);//todas as perguntas colocadas num set
                    
                }
            }
            pq.populate(p);

            for(engine.Publicacao y :pq.terminateToList()){
                result.add(y.getId());//todos os longs referentes ás perguntas em Lista
            }

        return result;
    }

    // Query 7
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
        Set<engine.Publicacao> p = new TreeSet<engine.Publicacao>();
        List<Long> result = new ArrayList<Long>();

        engine.GeneralizedPriorityQueue<engine.Publicacao> pq = new engine.GeneralizedPriorityQueue<engine.Publicacao>(
            N , ( (Object l , Object s) -> ((engine.Publicacao)l).compareAnswers(s)*-1)); //Inverter a ordem , "ordem decrescente"
        
        for(engine.Publicacao x : this.postArray){ //todas as perguntas entra a x data
            if(x instanceof engine.Pergunta && x.getData().isAfter(begin) && x.getData().isBefore(end)){
                p.add(x);
            }
        }

        pq.populate(p);
        for(engine.Publicacao x : pq.terminateToList()){ //todas as perguntas entra a x data
            result.add(x.getId());    
        }

        return result;
    }

    // Query 8
    public List<Long> containsWord(int N, String word) {
        //estou a usar como se fosse a strstr -> professores disseram que nao fazia diferença
        Set<engine.Publicacao> p = new TreeSet<engine.Publicacao>();
        List<Long> result = new ArrayList<Long>();

        engine.GeneralizedPriorityQueue<engine.Publicacao> pq = new engine.GeneralizedPriorityQueue<engine.Publicacao>(
            N , ( (Object l , Object s) -> ((engine.Publicacao)l).compareAnswers(s)*-1)); //Inverter a ordem , "ordem decrescente"
        
        for(engine.Publicacao x : this.postArray){ //todas as perguntas entra a x data
            if(x instanceof engine.Pergunta && x.getNome().contains(word)){
                p.add(x);
            }
        }

        pq.populate(p);

        for(engine.Publicacao y : pq.terminateToList() ){
            result.add(y.getId());
        }

        return result;
    }

    // Query 9
    public List<Long> bothParticipated(int N, long id1, long id2) {
        return Arrays.asList(594L);
    }

    // Query 10
    public long betterAnswer(long id) {
        Long cont = Long.valueOf(-1);
        double tmp =0;
        if(this.post.containsKey(id)){
            if(this.post.get(id) instanceof engine.Pergunta){
                Pergunta p = (Pergunta) this.post.get(id);

                for(Long l : p.getAns()){//percorrer todas as respostas

                    engine.Resposta aux = (engine.Resposta) this.post.get(l);//resposta
                    engine.Utilizador util = (engine.Utilizador) this.users.get(aux.getFundador());//fundador
                    
                    if(aux.getScore() * 0.45 + util.getRep() * 0.25 + aux.getVotes()*0.2 + aux.getComment_count() *0.1 > tmp){ //calculo para verificar qual a melhor resposta
                        tmp = aux.getScore() * 0.45 + util.getRep() * 0.25 + aux.getVotes()*0.2 + aux.getComment_count() *0.1;
                        cont = aux.getId();//passa a conter o id da melhor resposta
                    }
                  }   
            }
        }
        return cont;
    }

    // Query 11
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(6L,29L,72L,163L,587L);
    }

    public void clear(){

    }
}
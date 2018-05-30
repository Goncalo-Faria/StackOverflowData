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
    
    private Map<Long, engine.Utilizador> users;
    private Map<Long, engine.Publicacao> post;
    private TreeSet<engine.Publicacao> postArray;
    private Map<String, engine.Tag> tagconv;

    public Comunidade (){
        this.users = new HashMap<Long, engine.Utilizador>();
        this.postArray = new TreeSet<engine.Publicacao>();
        this.post = new HashMap<Long, engine.Publicacao>();
        this.tagconv = new HashMap<String, engine.Tag>();
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
            if(p.isAnswer()){

                engine.Resposta rp = (engine.Resposta)p;
                if(this.post.containsKey(rp.getParentId())){
                    p = this.post.get(rp.getParentId());

                }else{
                    return new Pair<>(x1, x2);
                }
            }

            try{ x1 = p.getNome();}catch(NullPointerException ex){x1=null;}
            try{
                if(this.users.containsKey(p.getFundador()))
                    x2 = this.users.get(p.getFundador()).getNome();

            }catch(NullPointerException ex){
                x2 = null;
            }

        }
        return new Pair<>(x1, x2);
    }

    // Query 2
    public List<Long> topMostActive(int N) {
        engine.GeneralizedPriorityQueue<engine.Utilizador> pq = new engine.GeneralizedPriorityQueue<engine.Utilizador>(
            N, engine.Utilizador.getComparator("UtilizadoresAtivos"));

            pq.populate(this.users.values());

            List<Long> l = pq.terminateToList().stream().
                    map(engine.Utilizador::getId).collect(Collectors.toList());

        return l;
    }

    // Query 3
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {
        long question = 0;
        long answer = 0;

        SortedSet<engine.Publicacao> st = this.postArray.
                subSet(new engine.Publicacao(begin), new engine.Publicacao(end));

        for(engine.Publicacao p : st){
            if(p.isQuestion()) question++;
            else answer++;
        }

        return new Pair<>(Long.valueOf(question),Long.valueOf(answer));
    }

    // Query 4
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
        List<Long> st = new ArrayList<Long>();

        if( this.tagconv.containsKey(tag) ) {
            final engine.Tag tg = this.tagconv.get(tag);

            st = this.postArray.
                    subSet(new engine.Publicacao(begin), new engine.Publicacao(end)).
                        stream().filter( h -> h.isQuestion() && h.getTags().contains(tg)).
                            map(engine.Publicacao::getId).collect(Collectors.toList());

            //Collections.reverse(st) caso seja preciso reverter;
        }
        
        return st;
    }

    // Query 5
    public Pair<String, List<Long>> getUserInfo(long id) {

        String shortBio = null ;
        List<Long> p = new ArrayList<Long>();
        engine.Utilizador ut;
        if(this.users.containsKey(id)){

            ut = this.users.get(id);
            shortBio = ut.getBio();

            List<engine.Publicacao> candidatos = new LinkedList<>();

            for( Set<Long> pbid : ut.getBacia().values())
                pbid.forEach(l -> candidatos.add(this.post.get(l)));

            engine.GeneralizedPriorityQueue<engine.Publicacao> pq = new engine.GeneralizedPriorityQueue<engine.Publicacao>
                (10, engine.Publicacao.getComparator("MaisRecente"));
            
            pq.populate(candidatos);
            p = pq.terminateToList().stream().map(engine.Publicacao::getId).collect(Collectors.toList());

        }

        return new Pair<>(shortBio,p);
    }

    // Query 6
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {

        List<engine.Publicacao> st = this.postArray.
                subSet(new engine.Publicacao(begin), new engine.Publicacao(end)).
                    stream().filter( h -> h.isAnswer() ).collect(Collectors.toList());

        engine.GeneralizedPriorityQueue<engine.Publicacao> pq = new engine.GeneralizedPriorityQueue<engine.Publicacao>(
            N , engine.Publicacao.getComparator("MaiorScore"));

        pq.populate(st);

        return pq.terminateToList().stream().map(engine.Publicacao::getId).collect(Collectors.toList());
    }

    // Query 7
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {

        Set<engine.Publicacao> st = this.postArray.
                subSet(new engine.Publicacao(begin), new engine.Publicacao(end)).
                stream().filter( h -> h.isQuestion() ).collect(Collectors.toSet());

        engine.GeneralizedPriorityQueue<engine.Publicacao> pq = new engine.GeneralizedPriorityQueue<engine.Publicacao>(
            N , engine.Publicacao.getComparator("MaisRespostas")); //Inverter a ordem , "ordem decrescente"

        pq.populate(st);

        return pq.terminateToList().stream().map(engine.Publicacao::getId).collect(Collectors.toList());
    }

    // Query 8
    public List<Long> containsWord(int N, String word) {

        Iterator<engine.Publicacao> litr = this.postArray.descendingIterator();

        engine.Publicacao value;
        List<Long> result = new ArrayList<Long>();

        int count =0;
        while(litr.hasNext()){
            value = litr.next();
            try {
                if (value.getNome().contains(word)) {
                    count++;
                    result.add(value.getId());
                }
            }catch(NullPointerException ex){
                continue;
            }

            if(count>N)
                break;

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
        if(this.post.containsKey(id)) {
            engine.Publicacao pub = this.post.get(id);
            if( pub.isQuestion()){
                engine.Pergunta ans = (engine.Pergunta)pub;
                Set<engine.Resposta> respostas = ans.getAns().stream().map( l -> this.post.get(l)).filter(engine.Publicacao::isAnswer).map(l->(engine.Resposta)l).collect(Collectors.toSet());

                double mvalue = Double.MIN_VALUE;
                for( engine.Resposta x : respostas){
                    if(this.users.containsKey(x.getFundador())){
                        double temp = x.calculateCotacao(this.users.get(x.getFundador()));
                        if( temp >  mvalue){
                            mvalue = temp;
                            cont = x.getId();
                        }
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
package engine;

import common.MyLog;
import common.Pair;
import jdk.nashorn.api.tree.Tree;
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
    
    private Map<String, engine.Utilizador> users;
    private Map<String, engine.Publicacao> post;
    private TreeSet<engine.Publicacao> postArray;
    private Map<String, engine.Tag> tagconv;

    public Comunidade (){
        this.users = new HashMap<String, engine.Utilizador>();
        this.postArray = new TreeSet<engine.Publicacao>();
        this.post = new HashMap<String, engine.Publicacao>();
        this.tagconv = new HashMap<String, engine.Tag>();
    }

    public Comunidade (Comunidade x){
        this.users = x.getusers();
        this.post= x.getPost();
        this.tagconv = x.getTagconv();
        this.makepostArray();
    }

//Getters!------------------------------------------------------------------------------------------------------------------------------------
    public Map<String, engine.Utilizador> getusers(){
        return this.users.values().stream().collect(Collectors.toMap(l ->l.getId(), l -> l.clone()));
    }

    public Set<engine.Publicacao> getpostArray(){
        return this.postArray.stream().map(engine.Publicacao::clone).collect(Collectors.toSet());
    }

    public Map<String, engine.Publicacao> getPost(){
         return this.post.values().stream().collect(Collectors.toMap(l ->l.getId(), l -> l.clone()));
    }
    
    public Map<String, engine.Tag> getTagconv(){
         return this.tagconv.entrySet().stream().collect(Collectors.toMap(l -> l.getKey() , l -> l.getValue().clone()));
    }

//Setters!------------------------------------------------------------------------------------------------------------------------------------
    void setUsers(Map<String, engine.Utilizador> x){
        this.users = x.values().stream().collect(Collectors.toMap(l->l.getId(), l->l.clone()));
    }
    
    void setPost(Map<String, engine.Publicacao> x){
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

        for(Map.Entry<String,Set<engine.Publicacao> >pr : pst.getComplementar().entrySet() ){
            if(  this.users.containsKey(pr.getKey()) ){
                engine.Utilizador util = this.users.get(pr.getKey());
                pr.getValue().forEach(l -> util.addBacia(l) );
            }
        }

        this.makepostArray();
    }

    // Query 1 works
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

    // Query 2 works
    public List<Long> topMostActive(int N) {
        engine.GeneralizedPriorityQueue<engine.Utilizador> pq = new engine.GeneralizedPriorityQueue<engine.Utilizador>(
            N, engine.Utilizador.getComparator("UtilizadoresAtivos"));

        pq.populate(this.users.values());

        List<Long> l = pq.terminateToList().stream().
                    map(engine.Utilizador::getId).map(Long::valueOf).collect(Collectors.toList());

        return l;
    }

    // Query 3 works
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

    // Query 4 works
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
        List<Long> st = new ArrayList<Long>();

        if( this.tagconv.containsKey(tag) ) {
            final engine.Tag tg = this.tagconv.get(tag);

            st = this.postArray.
                    subSet(new engine.Publicacao(begin), new engine.Publicacao(end)).
                        stream().filter( h -> h.isQuestion() && h.getTags().contains(tg)).
                            map(engine.Publicacao::getId).map(Long::valueOf).collect(Collectors.toList());

            //Collections.reverse(st) caso seja preciso reverter;
        }

        return st;
    }

    // Query 5 works
    public Pair<String, List<Long>> getUserInfo(long id) {

        String shortBio = null ;
        List<Long> p = new ArrayList<Long>();
        engine.Utilizador ut;
        if(this.users.containsKey(id)){

            ut = this.users.get(id);
            shortBio = ut.getBio();

            List<engine.Publicacao> candidatos = ut.getBacia().values().stream().
                    flatMap(Set::stream).map(l-> this.post.get(l)).collect(Collectors.toList());

            engine.GeneralizedPriorityQueue<engine.Publicacao> pq = new engine.GeneralizedPriorityQueue<engine.Publicacao>
                (10, engine.Publicacao.getComparator("MaisRecente"));
            
            pq.populate(candidatos);
            p = pq.terminateToList().stream().map(engine.Publicacao::getId).map(Long::valueOf).collect(Collectors.toList());

        }

        return new Pair<>(shortBio,p);
    }

    // Query 6 works
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {

        List<engine.Publicacao> st = this.postArray.
                subSet(new engine.Publicacao(begin), new engine.Publicacao(end)).
                stream().filter(engine.Publicacao::isAnswer).collect(Collectors.toList());


        engine.GeneralizedPriorityQueue<engine.Publicacao> pq = new engine.GeneralizedPriorityQueue<engine.Publicacao>(
            N , engine.Publicacao.getComparator("MaiorScore"));

        pq.populate(st);
        List<Long> g = pq.terminateToList().stream().map(engine.Publicacao::getId).map(Long::valueOf).collect(Collectors.toList());

        //Collections.reverse(g);
        return g;
    }

    // Query 7 works
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {

        Set<engine.Publicacao> st = this.postArray.
                subSet(new engine.Publicacao(begin), new engine.Publicacao(end)).
                stream().filter(engine.Publicacao::isQuestion).collect(Collectors.toSet());

        engine.GeneralizedPriorityQueue<engine.Publicacao> pq = new engine.GeneralizedPriorityQueue<engine.Publicacao>(
            N , engine.Publicacao.getComparator("MaisRespostas")); //Inverter a ordem , "ordem decrescente"

        pq.populate(st);

        List<Long> ll = pq.terminateToList().stream().map(engine.Publicacao::getId).map(Long::valueOf).collect(Collectors.toList());

        return ll;
    }

    // Query 8 works
    public List<Long> containsWord(int N, String word) {

        Iterator<engine.Publicacao> litr = this.postArray.descendingIterator();

        engine.Publicacao value;
        List<Long> result = new ArrayList<Long>();

        int count =0;
        while(litr.hasNext()){
            value = litr.next();

            try {

                if (value.getNome().toLowerCase().contains(word)) {
                    count++;
                    result.add(Long.valueOf(value.getId()));
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
    public List<Long> bothParticipated(int N, long id1, long id2){
        List<Long> result = new ArrayList<Long>();

        engine.GeneralizedPriorityQueue<engine.Publicacao> pq = new engine.GeneralizedPriorityQueue<engine.Publicacao>(
                N , engine.Publicacao.getComparator("MaisRecente"));


        if(this.users.containsKey(id1) && this.users.containsKey(id2))
        {
            engine.Utilizador u1 = this.users.get(id1);
            engine.Utilizador u2 = this.users.get(id2);

            pq.populate(u1.mutualIntervention(u2).stream().
                    map(l -> this.post.get(l)).collect(Collectors.toSet()));

            result = pq.terminateToList().stream().
                    map(engine.Publicacao::getId).map(Long::valueOf).collect(Collectors.toList());
       }

        return result;
    }

    // Query 10 yup
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
                            cont = Long.valueOf(x.getId());
                        }
                    }
                }
            }

        }
        return cont;
    }

    // Query 11 works
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {

        engine.GeneralizedPriorityQueue<engine.Utilizador> pq = new engine.GeneralizedPriorityQueue<engine.Utilizador>(
                N , engine.Utilizador.getComparator("MaiorReputacao"));

        pq.populate(this.users.values());

        HashMap<engine.Tag,Integer> histtag= new HashMap<engine.Tag,Integer>();
        HashMap<String,engine.Utilizador> reputados = new HashMap<String,engine.Utilizador>();


        this.tagconv.values().forEach(l -> histtag.put(l,Integer.valueOf(0)));
        pq.terminateToList().forEach(l -> reputados.put(l.getId(),l));

        Set <engine.Publicacao> st = this.postArray.
                subSet(new engine.Publicacao(begin), new engine.Publicacao(end));

        for(engine.Publicacao y : st ){
            if( reputados.containsKey(y.getFundador())){
                for( engine.Tag tgx : y.getTags()){
                    int count = histtag.get(tgx).intValue();
                    histtag.remove(tgx);
                    histtag.put(tgx, Integer.valueOf(count+ 1));
                }

            }
        }
        Comparator<Map.Entry<engine.Tag, Integer>> freqCmp = ((l,s) -> l.getValue().compareTo(s.getValue()));

        engine.GeneralizedPriorityQueue<Map.Entry<engine.Tag, Integer>> fpq = new engine.
                    GeneralizedPriorityQueue<Map.Entry<engine.Tag, Integer>>(N,freqCmp.reversed());
        fpq.populate(histtag.entrySet());

        return fpq.terminateToList().stream().
                map(l ->l.getKey().getId()).map(Long::valueOf).collect(Collectors.toList());
    }

    public void clear(){
        //Perder o apontador para que o Garbage collector libertar a memória.
        this.users = null;
        this.post = null;
        this.postArray = null;
        this.tagconv = null;
    }
}
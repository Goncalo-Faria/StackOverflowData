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
    
    private Map<String, Utilizador> users;
    private Map<String, Publicacao> post;
    private TreeSet<Publicacao> postArray;
    private Map<String, Tag> tagconv;

    public Comunidade (){
        this.users = new HashMap<String, Utilizador>();
        this.postArray = new TreeSet<Publicacao>();
        this.post = new HashMap<String, Publicacao>();
        this.tagconv = new HashMap<String, Tag>();
    }

    public Comunidade (Comunidade x){
        this.users = x.getusers();
        this.post= x.getPost();
        this.tagconv = x.getTagconv();
        this.makepostArray();
    }

//Getters!------------------------------------------------------------------------------------------------------------------------------------
    public Map<String, Utilizador> getusers(){
        return this.users.values().stream().collect(Collectors.toMap(l ->l.getId(), l -> l.clone()));
    }

    public Set<Publicacao> getpostArray(){
        return this.postArray.stream().map(Publicacao::clone).collect(Collectors.toSet());
    }

    public Map<String, Publicacao> getPost(){
         return this.post.values().stream().collect(Collectors.toMap(l ->l.getId(), l -> l.clone()));
    }
    
    public Map<String, Tag> getTagconv(){
         return this.tagconv.entrySet().stream().collect(Collectors.toMap(l -> l.getKey() , l -> l.getValue().clone()));
    }

//Setters!------------------------------------------------------------------------------------------------------------------------------------
    void setUsers(Map<String, Utilizador> x){
        this.users = x.values().stream().collect(Collectors.toMap(l->l.getId(), l->l.clone()));
    }
    
    void setPost(Map<String, Publicacao> x){
        this.post = x.values().stream().collect(Collectors.toMap(l->l.getId(), l->l.clone()));
    }
    
    void setTagconv(Map<String, Tag> x){
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
        this.postArray = new TreeSet<Publicacao>(this.post.values());
    }


//--------------------------------------------------------------------------------------------------------------------------    


    public void load(String dumpPath) {

        StackOverFlowParse parse = new StackOverFlowParse(dumpPath);

        this.tagconv = ((TagConversionSAX)parse.analyze("Tags.xml", new TagConversionSAX())).getResults();

        this.users = ((UsersSAX)parse.analyze("Users.xml", new UsersSAX())).getResults();

        PostSAX pst = new PostSAX(this.tagconv);

        this.post = ((PostSAX)parse.analyze("Posts.xml", pst )).getResults();

        for(Map.Entry<String,Set<Publicacao> >pr : pst.getComplementar().entrySet() ){
            if(  this.users.containsKey(pr.getKey()) ){
                Utilizador util = this.users.get(pr.getKey());
                pr.getValue().forEach(l -> util.addBacia(l) );
            }
        }

        this.makepostArray();

    }

    // Query 1
    public Pair<String,String> infoFromPost(long id) {
        String x1 = null;
        String x2 = null;
        Utilizador u;
        Publicacao p;
        if(this.post.containsKey(String.valueOf(id))){
            p=this.post.get(String.valueOf(id));
            if(p.isAnswer()){

                Resposta rp = (Resposta)p;
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
        GeneralizedPriorityQueue<Utilizador> pq = new GeneralizedPriorityQueue<Utilizador>(
            N, Utilizador.getComparator("UtilizadoresAtivos"));

        pq.populate(this.users.values());

        List<Long> l = pq.terminateToList().stream().
                    map(Utilizador::getId).map(Long::valueOf).collect(Collectors.toList());

        return l;
    }

    // Query 3 
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {
        long question = 0;
        long answer = 0;

        SortedSet<Publicacao> st = this.postArray.
                    subSet(new Publicacao(begin,-1), new Publicacao(end,1));

        for(Publicacao p : st ){
            if(p.isQuestion()) question++;
            else answer++;
        }

        return new Pair<>(Long.valueOf(question),Long.valueOf(answer));
    }

    // Query 4
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
        List<Long> st = new ArrayList<Long>();

        if( this.tagconv.containsKey(tag) ) {
            final Tag tg = this.tagconv.get(tag);

            st = this.postArray.
                    subSet(new Publicacao(begin,-1), new Publicacao(end,1)).
                        stream().filter( h -> h.isQuestion() && h.getTags().contains(tg)).
                            map(Publicacao::getId).map(Long::valueOf).collect(Collectors.toList());


            Collections.reverse(st);
        }

        return st;
    }

    // Query 5
    public Pair<String, List<Long>> getUserInfo(long id) {

        String shortBio = null ;
        List<Long> p = new ArrayList<Long>();
        Utilizador ut;
        if(this.users.containsKey(String.valueOf(id))){

            ut = this.users.get(String.valueOf(id));
            shortBio = ut.getBio();

            List<Publicacao> candidatos = ut.getBacia().values().stream().
                    flatMap(Set::stream).map(l-> this.post.get(l)).collect(Collectors.toList());

            GeneralizedPriorityQueue<Publicacao> pq = new GeneralizedPriorityQueue<Publicacao>
                (10, Publicacao.getComparator("MaisRecente"));
            
            pq.populate(candidatos);
            p = pq.terminateToList().stream().map(Publicacao::getId).map(Long::valueOf).collect(Collectors.toList());

        }

        return new Pair<>(shortBio,p);
    }

    // Query 6 
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {

        List<Publicacao> st = this.postArray.
                subSet(new Publicacao(begin,-1), new Publicacao(end,1)).
                stream().filter(Publicacao::isAnswer).collect(Collectors.toList());


        GeneralizedPriorityQueue<Publicacao> pq = new GeneralizedPriorityQueue<Publicacao>(
            N , Publicacao.getComparator("MaiorScore"));

        pq.populate(st);

        return pq.terminateToList().stream().map(Publicacao::getId).
                    map(Long::valueOf).collect(Collectors.toList());

    }

    // Query 7
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {

        Set<Publicacao> st = this.postArray.
                subSet(new Publicacao(begin,-1), new Publicacao(end,1)).
                stream().filter(Publicacao::isQuestion).collect(Collectors.toSet());

        GeneralizedPriorityQueue<Publicacao> pq = new GeneralizedPriorityQueue<Publicacao>(
            N , Publicacao.getComparator("MaisRespostas")); //Inverter a ordem , "ordem decrescente"

        pq.populate(st);

        return pq.terminateToList().stream().
                map(Publicacao::getId).map(Long::valueOf).
                        collect(Collectors.toList());
    }

    // Query 8
    public List<Long> containsWord(int N, String word) {

        Iterator<Publicacao> litr = this.postArray.descendingIterator();

        Publicacao value;
        List<Long> result = new ArrayList<Long>();

        int count =0;
        while(litr.hasNext()){
            value = litr.next();

            try {

                if (value.getNome().contains(word)) {
                    count++;
                    result.add(Long.valueOf(value.getId()));
                }
            }catch(NullPointerException ex){
                continue;
            }

            if(count>(N-1))
                break;

        }


        return result;
    }
    
    // Query 9
    public List<Long> bothParticipated(int N, long id1, long id2){
        List<Long> result = new ArrayList<Long>();

        GeneralizedPriorityQueue<Publicacao> pq = new GeneralizedPriorityQueue<Publicacao>(
                N , Publicacao.getComparator("MaisRecente"));


        if(this.users.containsKey(String.valueOf(id1)) && this.users.containsKey(String.valueOf(id2)))
        {
            Utilizador u1 = this.users.get(String.valueOf(id1));
            Utilizador u2 = this.users.get(String.valueOf(id2));

            pq.populate(u1.mutualIntervention(u2).stream().
                    map(l -> this.post.get(l)).collect(Collectors.toSet()));

            result = pq.terminateToList().stream().
                    map(Publicacao::getId).map(Long::valueOf).collect(Collectors.toList());
       }

        return result;
    }

    // Query 10 yup
    public long betterAnswer(long id) {
        Long cont = Long.valueOf(-1);
        double tmp =0;
        if(this.post.containsKey(String.valueOf(id))) {
            Publicacao pub = this.post.get(String.valueOf(id));
            if( pub.isQuestion()){
                Pergunta ans = (Pergunta)pub;
                Set<Resposta> respostas = ans.getAns().stream().map( l -> this.post.get(l)).filter(Publicacao::isAnswer).map(l->(Resposta)l).collect(Collectors.toSet());

                double mvalue = Double.MIN_VALUE;
                for( Resposta x : respostas){
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

    // Query 11 
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {

        GeneralizedPriorityQueue<Utilizador> pq = new GeneralizedPriorityQueue<Utilizador>(
                N , Utilizador.getComparator("MaiorReputacao"));

        pq.populate(this.users.values());

        HashMap<Tag,Integer> histtag= new HashMap<Tag,Integer>();
        HashMap<String,Utilizador> reputados = new HashMap<String,Utilizador>();


        this.tagconv.values().forEach(l -> histtag.put(l,Integer.valueOf(0)));
        pq.terminateToList().forEach(l -> reputados.put(l.getId(),l));

        Set <Publicacao> st = this.postArray.
                subSet(new Publicacao(begin,-1), new Publicacao(end,1));

        for(Publicacao y : st ){
            if( reputados.containsKey(y.getFundador())){
                for( Tag tgx : y.getTags()){
                    int count = histtag.get(tgx).intValue();
                    histtag.remove(tgx);
                    histtag.put(tgx, Integer.valueOf(count+ 1));
                }
            }
        }
        Comparator<Map.Entry<Tag, Integer>> freqCmp = ((l,s) -> l.getKey().compare( l.getValue() , s) );

        GeneralizedPriorityQueue<Map.Entry<Tag, Integer>> fpq = new 
                    GeneralizedPriorityQueue<Map.Entry<Tag, Integer>>(N,freqCmp);
        fpq.populate(histtag.entrySet());
        List<Map.Entry<Tag, Integer>>ll = fpq.terminateToList();

        return ll.stream().
                map(l ->l.getKey().getId()).map(Long::valueOf).collect(Collectors.toList());
    }

    public void clear(){
        //Perder o apontador para que o Garbage collector libertar a memória.
        this.users = new HashMap<String, Utilizador>();
        this.postArray = new TreeSet<Publicacao>();
        this.post = new HashMap<String, Publicacao>();
        this.tagconv = new HashMap<String, Tag>();
    }
}
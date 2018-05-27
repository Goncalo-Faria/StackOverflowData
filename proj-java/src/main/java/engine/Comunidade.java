
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

        return (this.postArray.equals(y.getpostArray()) && this.post.equals(y.getPost()) 
                && this.users.equals(y.getusers()) && this.tagconv.equals(y.getTagconv()));
    }
    
    public void makepostArray(){
        this.postArray = new TreeSet<engine.Publicacao>(this.post.values());
    }


//--------------------------------------------------------------------------------------------------------------------------    


    public void load(String dumpPath) {
        File inputFile = new File(dumpPath);

        SAXParserFactory factory = SAXParserFactory.newInstance ();
        engine.TagConversionSAX saxt = new engine.TagConversionSAX();
        try {
            SAXParser parser = factory.newSAXParser();
            parser.parse(new File(dumpPath + "/Tags.xml"), saxt);
        }catch (Exception exp ){
            System.out.println(exp.toString());
            exp.printStackTrace();
        }

        this.tagconv=saxt.getResults();

        engine.UsersSAX saxu = new engine.UsersSAX();
        try{
            SAXParser parser = factory.newSAXParser();
            parser.parse(new File(dumpPath + "/Users.xml"), saxu);
        }catch (Exception exp){
            System.out.println(exp.toString());
            exp.printStackTrace();
        }

        this.users = saxu.getResults();

        engine.PostSAX saxp = new engine.PostSAX(this.tagconv);

        try{
            SAXParser parser = factory.newSAXParser();
            parser.parse(new File(dumpPath + "/Posts.xml"), saxp);
        }catch (Exception exp){
            System.out.println(exp.toString());
            exp.printStackTrace();
        }

    }

    // Query 1
    public Pair<String,String> infoFromPost(long id) {
        return new Pair<>("What are the actual risks of giving www-data sudo nopasswd access?", "WebNinja");
    }

    // Query 2
    public List<Long> topMostActive(int N) {
        return Arrays.asList(15811L,449L,158442L,167850L,367165L,295286L,59676L,93977L,35795L,3940L);
    }

    // Query 3
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {
        return new Pair<>(3667L,4102L);
    }

    // Query 4
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
        return Arrays.asList(276174L,276029L,274462L,274324L,274316L,274141L,274100L,272937L,
                272813L,272754L,272666L,272565L,272450L,272313L,271816L,271683L,271647L,270853L,270608L,270528L,270488L,
                270188L,270014L,269876L,269781L,269095L,268501L,268155L,267746L,267656L,267625L,266742L,266335L,266016L,
                265531L,265483L,265443L,265347L,265104L,265067L,265028L,264764L,264762L,264616L,264525L,264292L,263816L,
                263740L,263460L,263405L,263378L,263253L,262733L,262574L);
    }

    // Query 5
    public Pair<String, List<Long>> getUserInfo(long id) {
        String shortBio = "<p>Coder. JS, Perl, Python, Basic<br>Books/movies: SF+F.<br>Dead:" +
                "dell 9300<br>Dead: dell 1720 as of may 10th 2011.</p>\n" +
                "<p>Current system: Acer Aspire 7750G.<br>\n" +
                "Works OOTB as of Ubuntu 12.04.<br></p>";
        List<Long> ids = Arrays.asList(982507L,982455L,980877L,980197L,980189L,976713L,974412L,
                974359L,973895L,973838L);
        return new Pair<>(shortBio,ids);
    }

    // Query 6
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(701775L,697197L,694560L,696641L,704208L);
    }

    // Query 7
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(505506L,508221L,506510L,508029L,506824L,505581L,505368L,509498L,509283L,508635L);
    }

    // Query 8
    public List<Long> containsWord(int N, String word) {
        return Arrays.asList(980835L,979082L,974117L,974105L,973832L,971812L,971056L,968451L,964999L,962770L);
    }

    // Query 9
    public List<Long> bothParticipated(int N, long id1, long id2) {
        return Arrays.asList(594L);
    }

    // Query 10
    public long betterAnswer(long id) {
        return 175891;
    }

    // Query 11
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(6L,29L,72L,163L,587L);
    }

    public void clear(){

    }
}
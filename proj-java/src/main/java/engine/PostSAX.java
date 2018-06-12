package engine;

import org.xml.sax.Attributes;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class PostSAX extends SAXStackOverflow {
    private HashMap<String,Set<Publicacao>> users; /*-> fundador -> publicacoes*/
    private HashMap<String, Set<String>> answers; /* correspondencia pergunta -> respostas */
    private HashMap <String,Publicacao> posts;
    private Map<String, Tag> tags;

    public PostSAX(Map<String, Tag> tags){
        super();
        this.users = new HashMap<String,Set<Publicacao>>();
        this.posts = new HashMap<String, Publicacao>();
        this.tags = tags;
        this.answers =  new HashMap<String, Set<String>>();
    }

    public Map<String, Publicacao> getResults () {

        for( Map.Entry<String,Set<String>> x :this.answers.entrySet()){
            if( this.posts.containsKey(x.getKey()) ){
                Publicacao pub = this.posts.get(x.getKey());
                    if( pub.isQuestion() ){
                        Pergunta quest = (Pergunta)pub;
                        quest.setAns(x.getValue());
                    }
            }
        }

        return this.posts;
    }
    public HashMap<String,Set<Publicacao>> getComplementar(){ return this.users; }

    public void rowInspector( Attributes atts){


        String nome = atts.getValue("Title");
        String id = atts.getValue("Id");
        String fundador = atts.getValue("OwnerUserId");
        int postType = Long.valueOf(atts.getValue("PostTypeId")).intValue();
        int commentCount = Long.valueOf(atts.getValue("CommentCount")).intValue();
        int score = Long.valueOf(atts.getValue("Score")).intValue();
        String dat = atts.getValue("CreationDate");

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        LocalDate date = LocalDate.parse(dat.substring(0,10), formatter);
        Publicacao newlyCreatedPublication;



        if( postType == 1){
            newlyCreatedPublication = new Pergunta(id,nome,score,commentCount,date,fundador);
        }else if( postType == 2 ){
            String parentid = atts.getValue("ParentId");
            if(this.answers.containsKey(parentid)){
                this.answers.get(parentid).add(id);
            } else {
                Set<String> val = new HashSet<String>();
                val.add(id);
                this.answers.put(parentid,val);
            }
            newlyCreatedPublication = new Resposta(id, nome, score, commentCount, date, parentid,fundador);
        }else{return;}
        String tagfield = atts.getValue("Tags");
        if(tagfield != null) {
            for (String tagsnip : Tag.obtainTagNames(tagfield)) {
                if (tags.containsKey(tagsnip)) {
                    newlyCreatedPublication.addTag(tags.get(tagsnip).clone());
                }
            }
        }

        if( this.users.containsKey(fundador) ){
            this.users.get(fundador).add(newlyCreatedPublication);
        }else{
            Set<Publicacao> trail = new HashSet<Publicacao>();
            trail.add(newlyCreatedPublication);
            this.users.put(fundador,trail);

        }

        this.posts.put(id,newlyCreatedPublication);

    }
}

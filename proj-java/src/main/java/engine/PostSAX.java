package engine;

import com.sun.jdi.LongValue;
import org.xml.sax.Attributes;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class PostSAX extends engine.SAXStackOverflow {
    private HashMap<Long,Set<engine.Publicacao>> users; /*serve para preencher a bacia*/
    private HashMap<Long, Set<Long>> answers; /* correspondencia pergunta -> respostas */
    private HashMap <Long,engine.Publicacao> posts; /*-> fundador -> publicacoes*/
    private Map<String, engine.Tag> tags;

    public PostSAX(Map<String, engine.Tag> tags){
        super();
        this.users = new HashMap<Long,Set<engine.Publicacao>>();
        this.posts = new HashMap<Long, engine.Publicacao>();
        this.tags = tags;
        this.answers =  new HashMap<Long, Set<Long>>();
    }

    public Map<Long, engine.Publicacao> getResults () {

        for( Map.Entry<Long,Set<Long>> x :this.answers.entrySet()){
            if( this.posts.containsKey(x.getKey()) ){
                engine.Publicacao pub = this.posts.get(x.getKey());
                    if( pub.isQuestion() ){
                        engine.Pergunta quest = (engine.Pergunta)pub;
                        quest.setAns(x.getValue());
                    }
            }
        }

        return this.posts;
    }
    public HashMap<Long,Set<engine.Publicacao>> getComplementar(){ return this.users; }

    public void rowInspector( Attributes atts){


        String nome = atts.getValue("Title");
        Long id = Long.valueOf(atts.getValue("Id"));
        Long fundador = Long.valueOf(atts.getValue("OwnerUserId"));
        int postType = Long.valueOf(atts.getValue("PostTypeId")).intValue();
        int commentCount = Long.valueOf(atts.getValue("CommentCount")).intValue();
        int score = Long.valueOf(atts.getValue("Score")).intValue();
        String dat = atts.getValue("CreationDate");

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        LocalDate date = LocalDate.parse(dat.substring(0,10), formatter);
        engine.Publicacao newlyCreatedPublication;



        if( postType == 1){
            newlyCreatedPublication = new engine.Pergunta(id,nome,score,commentCount,0,date);
        }else if( postType == 2 ){
            Long parentid = Long.valueOf(atts.getValue("ParentId"));
            if(this.answers.containsKey(parentid)){
                this.answers.get(parentid).add(id);
            } else {
                Set<Long> val = new HashSet<Long>();
                val.add(id);
                this.answers.put(parentid,val);
            }
            newlyCreatedPublication = new engine.Resposta(id, nome, score, commentCount,0, date, parentid);
        }else{return;}
        String tagfield = atts.getValue("Tags");
        if(tagfield != null) {
            for (String tagsnip : engine.Tag.obtainTagNames(tagfield)) {
                if (tags.containsKey(tagsnip)) {
                    newlyCreatedPublication.addTag(tags.get(tagsnip).clone());
                }
            }
        }

        if( this.users.containsKey(fundador) ){
            this.users.get(fundador).add(newlyCreatedPublication);
        }else{
            Set<engine.Publicacao> trail = new HashSet<engine.Publicacao>();
            trail.add(newlyCreatedPublication);
            this.users.put(fundador,trail);

        }

        this.posts.put(id,newlyCreatedPublication);

    }
}

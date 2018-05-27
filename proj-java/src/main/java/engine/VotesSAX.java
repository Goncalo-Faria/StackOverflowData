package engine;

import org.xml.sax.Attributes;

import java.util.HashMap;
import java.util.Map;

public class VotesSAX extends engine.SAXStackOverflow {

    private Map<Long,engine.Publicacao> posts;

    public VotesSAX(Map<Long, engine.Publicacao> posts) {
        this.posts = posts;
    }

    public void rowInspector(Attributes atts){

        Long id = Long.valueOf(atts.getValue("PostId"));
        if( this.posts.containsKey(id)){
            int type = Integer.valueOf(atts.getValue("VoteTypeId")).intValue();
            engine.Publicacao pub = this.posts.get(id);

            switch(type){
                case 2: pub.incUpVotes();break;
                case 3: pub.decDownVotes();break;
            }

        }

    }

    public Map<Long,engine.Publicacao> getResults(){
        return this.posts;
    }

}


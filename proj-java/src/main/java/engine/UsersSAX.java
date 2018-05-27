package engine;

import org.xml.sax.Attributes;

import java.util.HashMap;
import java.util.Map;

public class UsersSAX extends engine.SAXStackOverflow {
    private HashMap<Long, engine.Utilizador> users;

    public UsersSAX(){
        super();
        this.users = new HashMap<Long, engine.Utilizador>();
    }

    public Map<Long, engine.Utilizador> getResults () {
        return this.users;
    }

    public void rowInspector( Attributes atts){

        Long id = Long.valueOf(atts.getValue("Id"));
        String displayname = atts.getValue("DisplayName");
        int reputation = Long.valueOf(atts.getValue("Reputation")).intValue();
        int votes = Long.valueOf(atts.getValue("UpVotes")).
                intValue() - Long.valueOf(atts.getValue("DownVotes")).intValue();
        String shortbio = atts.getValue("AboutMe");

        if( id.intValue()>0){
            this.users.put(id,new engine.Utilizador(id, displayname,0,0, shortbio, reputation));
        }
    }
}

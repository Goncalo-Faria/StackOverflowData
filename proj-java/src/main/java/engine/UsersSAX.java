package engine;

import org.xml.sax.Attributes;

import java.util.HashMap;
import java.util.Map;

public class UsersSAX extends engine.SAXStackOverflow {
    private HashMap<String, engine.Utilizador> users;

    public UsersSAX(){
        super();
        this.users = new HashMap<String, engine.Utilizador>();
    }

    public Map<String, engine.Utilizador> getResults () {
        return this.users;
    }

    public void rowInspector( Attributes atts){

        String id = atts.getValue("Id");
        String displayname = atts.getValue("DisplayName");
        int reputation = Long.valueOf(atts.getValue("Reputation")).intValue();
        //int votes = Long.valueOf(atts.getValue("UpVotes")).
          //      intValue() - Long.valueOf(atts.getValue("DownVotes")).intValue();
        String shortbio = atts.getValue("AboutMe");

        this.users.put(id,new engine.Utilizador(id, displayname,0,0, shortbio, reputation));
    }
}

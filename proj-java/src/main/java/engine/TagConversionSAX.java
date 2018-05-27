package engine;

import org.xml.sax.Attributes;
import java.util.HashMap;
import java.util.Map;

public class TagConversionSAX extends engine.SAXStackOverflow {
    private Map<String, engine.Tag> tags;

    public TagConversionSAX(){
        super();
        this.tags = new HashMap<String, engine.Tag>();
    }

    public Map<String, engine.Tag> getResults () {
        return this.tags;
    }

    public void rowInspector( Attributes atts){
        Long id = Long.valueOf(atts.getValue("Id"));
        String tagname = atts.getValue("TagName");
        this.tags.put(tagname,new engine.Tag(id,tagname));
    }
}

package engine;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.File;

public class StackOverFlowParse {

    private String path;
    private SAXParserFactory factory;

    public StackOverFlowParse(String path) {
        this.path = path;
        this.factory = SAXParserFactory.newInstance ();
    }

    public SAXStackOverflow analyze( String file , SAXStackOverflow sax){

        try{
            SAXParser parser = this.factory.newSAXParser();
            parser.parse(new File(this.path + file), sax);
        }catch (Exception exp) {
            System.out.println(exp.toString());
            exp.printStackTrace();
        }
        return sax;
    }
}

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import java.util.HashMap;
import java.util.Map;

public abstract class SAXStackOverflow extends DefaultHandler {



    public SAXStackOverflow() {

    }

    abstract public void rowInspector( Attributes atts);

    @Override
    public void startDocument () throws SAXException {
        System.out.println ("Start parse XML ...");
    }

    @Override
    public void startElement (String namespaceURI, String localName, String qName, Attributes atts) throws SAXException {
        System.out.println(qName);

        if(localName.equalsIgnoreCase("row")){
            rowInspector(atts);
        }
        super.startElement(namespaceURI, localName, qName, atts);
    }

    @Override
    public void endElement (String namespaceURI, String localName, String qName) throws SAXException {

    }

    @Override
    public void endDocument () {
        System.out.println ("Stop parse XML ...");
    }
}

package engine;

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
    }

    @Override
    public void startElement (String namespaceURI, String localName, String qName, Attributes atts) throws SAXException {

        if(qName.equals("row")){
            rowInspector(atts);
        }
        //super.startElement(namespaceURI, localName, qName, atts);
    }

    @Override
    public void endElement (String namespaceURI, String localName, String qName) throws SAXException {

    }

    @Override
    public void endDocument () {

    }
}

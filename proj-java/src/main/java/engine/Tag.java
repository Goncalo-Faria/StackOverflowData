package engine;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

public class Tag{
    private Long id;
    private String nome;
    /**ADD HASH CODE */

    static Set<String> obtainTagNames(String str){
        HashSet<String> conj = new HashSet<String>();
        int count = 0;
        int st,end;
        if(str != null) {
            while (count < str.length()) {
                st = str.indexOf('<', count) + 1;
                end = str.indexOf('>', st);

                String sub = str.substring(st , end);
                conj.add(sub);
                count += 2 + sub.length();
            }
        }

        return conj;
    }

    public Tag(){
        this.id = Long.valueOf(-1);
        this.nome = "nenhum";
    }

    public Tag(Long x, String y){
        this.id = x;
        this.nome = y;
    }

    public Tag(Tag x){
        this.id = x.getId();
        this.nome = x.getNome();
    }
    
//Getters!----------------------------------------------------------------------------------------------------------------
    public Long getId(){
        return this.id;
    }

    public String getNome(){
        return this.nome;
    }

//Setters!----------------------------------------------------------------------------------------------------------------
    public void setId(Long x){
        this.id = x;
    }

    public void setNome(String x){
        this.nome = x;
    }

// ---------------------------------------------------------------------------------------------------------------------------

    public Tag clone(){
        return new Tag(this);
    }

    public boolean equals(Object x){
        if (this == x) return true;
        if ( !(x instanceof engine.Tag) ) return false;
        Tag y = (Tag) x;
        return (y.getNome().equals(this.getNome()) && y.getId().equals((this.getId())));
    }


    @Override
    public int hashCode() {

        return getId().hashCode();
    }
}
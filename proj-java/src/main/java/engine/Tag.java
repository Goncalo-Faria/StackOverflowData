package engine;
import java.util.Objects;

public class Tag{
    Long id;
    String nome;  
    /**ADD HASH CODE */

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
        if ( !(x instanceof Pergunta) ) return false;
        Tag y = (Tag) x;
        return (y.getNome().equals(this.getNome()) && y.getId().equals((this.getId())));
    }


    @Override
    public int hashCode() {

        return getId().hashCode() + getNome().hashCode();
    }
}
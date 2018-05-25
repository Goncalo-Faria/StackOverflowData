public class Tag{
    Long id;
    String nome;

    public Tag(){
        this.id = new Long(-1);
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
        if (x.getClass() != getClass() ||  x == null) return false;
        Tag y = (Tag) x;
        return (y.getNome().equals(this.getNome()) && y.getId().equals((this.getId())));
    }

}
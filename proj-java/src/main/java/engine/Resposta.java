package engine;
import java.time.LocalDate;
import java.util.Objects;

public class Resposta extends Publicacao {

    private String parentID;

    /**
     * Construtor parametrisado de Respota.
     */
    public Resposta(String id, String nome, int score, int comment_count, LocalDate data, String parentID,String fundador) {
        super(id, nome, score, comment_count, data,fundador);
        this.parentID = parentID;

    }

    /**
     * Atribui o idenficador da publicação a se esta resposta responde.
     */
    public void setParentID(String parentID) {
        this.parentID = parentID;
    }

    /**
     * Obtém o identificador do publicação a se esta resposta responde.
     */
    public String getParentId(){return this.parentID;}

    /**
     * Calcula a cotacão desta pergunta no referido utilizador.
     */
    public double calculateCotacao(Utilizador u){
        double rep = u.getRep();
        return rep*0.25 + this.getScore()*0.2 + this.getComment_count()*0.1 + this.getScore()*0.45;
    }

    /**
     * Verifica a igualdade entre objetos.
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Resposta)) return false;
        if (!super.equals(o)) return false;
        Resposta resposta = (Resposta) o;
        return (this.parentID.equals(resposta.getParentId()));
    }

}
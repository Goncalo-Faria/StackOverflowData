package engine;
import java.time.LocalDate;
import java.util.Objects;

public class Resposta extends engine.Publicacao {

    private Long parentID;


    public Resposta() {
        super();
        this.parentID = Long.valueOf(-1);

    }

    public Resposta(Long id, String nome, int score, int comment_count, int votes, LocalDate data, Long parentID) {
        super(id, nome, score, comment_count, votes, data);
        this.parentID = parentID;

    }


    public void setParentID(Long parentID) {
        this.parentID = parentID;
    }

    public Long getParentId(){return this.parentID;}

    public double calculateCotacao(engine.Utilizador u){
        double rep = u.getRep();
        return rep*0.25 + this.getVotes()*0.2 + this.getComment_count()*0.1 + this.getScore()*0.45;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Resposta)) return false;
        if (!super.equals(o)) return false;
        Resposta resposta = (Resposta) o;
        return (this.parentID.equals(resposta.getParentId()));
    }

}
import java.time.LocalDate;
import java.util.Objects;

public class Resposta extends Publicacao{

    Long fundador;

    public Resposta() {
        this.fundador = Long.valueOf(-1);;
    }

    public Resposta(Long id, String nome, int score, int comment_count, int votes, char type, LocalDate data, Long fundador) {
        super(id, nome, score, comment_count, votes, type, data);
        this.fundador = fundador;
    }


    public void setFundador(Long fundador) {
        this.fundador = fundador;
    }

    public Long getFundador(){return this.fundador;}

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Resposta)) return false;
        if (!super.equals(o)) return false;
        Resposta resposta = (Resposta) o;
        return (this.fundador.equals(resposta.getFundador()));
    }

}
package engine;
import java.time.LocalDate;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;
import java.util.TreeSet;

public class Pergunta extends engine.Publicacao {

    private Set<Long> ans;

    public Pergunta(Long id, String nome, int score, int comment_count, int votes, LocalDate data,Long fundador) {
        super(id, nome, score, comment_count, votes, data,fundador);
        this.ans = new HashSet<Long>();
    }

    public Pergunta(Pergunta x) {
        super(x);
        this.ans = x.getAns();
    }

    public void setAns(Set<Long> ans) {
        this.ans = new HashSet<>(ans);
    }

    public Set<Long> getAns(){return (new HashSet<Long>(this.ans));}

    public int getAnsCount(){return this.ans.size();}

    public void addAns(Long x){
        this.ans.add(x);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Pergunta)) return false;
        if (!super.equals(o)) return false;
        Pergunta pergunta = (Pergunta) o;
        return this.ans.containsAll( pergunta.getAns());
    }

}
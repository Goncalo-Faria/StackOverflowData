package engine;
import java.time.LocalDate;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;
import java.util.TreeSet;

public class Pergunta extends Publicacao {

    private Set<String> ans;

    public Pergunta(String id, String nome, int score, int comment_count, LocalDate data,String fundador) {
        super(id, nome, score, comment_count, data,fundador);
        this.ans = new HashSet<String>();
    }

    public Pergunta(Pergunta x) {
        super(x);
        this.ans = x.getAns();
    }

    public void setAns(Set<String> ans) {
        this.ans = new HashSet<>(ans);
    }

    public Set<String> getAns(){return (new HashSet<String>(this.ans));}

    public int getAnsCount(){return this.ans.size();}

    public void addAns(String x){
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
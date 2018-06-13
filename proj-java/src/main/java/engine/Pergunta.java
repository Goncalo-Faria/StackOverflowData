package engine;
import java.time.LocalDate;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;
import java.util.TreeSet;

public class Pergunta extends Publicacao {

    private Set<String> ans;

    /**
     * Construtor parametrisado de Pergunta.
     */
    public Pergunta(String id, String nome, int score, int comment_count, LocalDate data,String fundador) {
        super(id, nome, score, comment_count, data,fundador);
        this.ans = new HashSet<String>();
    }
    /**
    * Construtor de cópia de Pergunta.
    */
    public Pergunta(Pergunta x) {
        super(x);
        this.ans = x.getAns();
    }

    /**
    * Preenche o conjunto de respostas.
    */
    public void setAns(Set<String> ans) {
        this.ans = new HashSet<>(ans);
    }

     /**
     * Obtêm o conjunto de respostas.
     */
    public Set<String> getAns(){return (new HashSet<String>(this.ans));}

     /**
     * Obtem o número de respostas.
     */
    public int getAnsCount(){return this.ans.size();}

     /**
     * Adiciona uma resposta.
     */
    public void addAns(String x){
        this.ans.add(x);
    }

     /**
     * Método equals
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Pergunta)) return false;
        if (!super.equals(o)) return false;
        Pergunta pergunta = (Pergunta) o;
        return this.ans.containsAll( pergunta.getAns());
    }

}
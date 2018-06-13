package engine;

import java.util.HashSet;
import java.util.Map;
import java.util.Objects;
import java.util.Set;

public class Tag {
    private String id;
    private String nome;

    static Set<String> obtainTagNames(String str) {
        HashSet<String> conj = new HashSet<String>();
        int count = 0;
        int st, end;
        if (str != null) {
            while (count < str.length()) {
                st = str.indexOf('<', count) + 1;
                end = str.indexOf('>', st);

                String sub = str.substring(st, end);
                conj.add(sub);
                count += 2 + sub.length();
            }
        }

        return conj;
    }

    /**
     * Construtor vazio de Tag.
     */
    public Tag() {
        this.id = null;
        this.nome = "nenhum";
    }
    /**
     * Construtor parametrisado de Tag.
     */
    public Tag(String x, String y) {
        this.id = x;
        this.nome = y;
    }

    /**
     * Construtor de cópia de Tag.
     */
    public Tag(Tag x) {
        this.id = x.getId();
        this.nome = x.getNome();
    }

    // Getters!----------------------------------------------------------------------------------------------------------------
    /**
     * Obtêm o idenficador.
     */
    public String getId() {
        return this.id;
    }

    /**
     * Obtêm o nome.
     */
    public String getNome() {
        return this.nome;
    }

    // Setters!----------------------------------------------------------------------------------------------------------------
    /**
     * Atribui um identicador.
     */
    public void setId(String x) {
        this.id = x;
    }

    /**
     * Atribui um nome.
     */
    public void setNome(String x) {
        this.nome = x;
    }

    // ---------------------------------------------------------------------------------------------------------------------------
    /**
     * Obtêm uma cópia deste objeto.
     */
    public Tag clone() {
        return new Tag(this);
    }

    /**
     * Verifica a igualdade entre objetos.
     */
    public boolean equals(Object x) {
        if (this == x)
            return true;
        if (!(x instanceof Tag))
            return false;
        Tag y = (Tag) x;
        return (y.getNome().equals(this.getNome()) && y.getId().equals((this.getId())));
    }

    public int compare(Integer oc, Map.Entry<Tag, Integer> other) {
        int fs = other.getValue().compareTo(oc);

        if (fs == 0) {
            fs = Long.valueOf(this.id).compareTo(Long.valueOf(other.getKey().getId()));
        }
        return fs;
    }

    @Override
    public int hashCode() {

        return getId().hashCode();
    }
}
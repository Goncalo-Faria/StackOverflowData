package engine;
import java.util.*;

public class GeneralizedPriorityQueue<E> {

    private PriorityQueue<E> q;
    private int fixedsize;
    private Comparator priority;

    public GeneralizedPriorityQueue(int n, Comparator priority ) {
        this.q = new PriorityQueue<E>(priority.reversed());
        this.fixedsize = n;
        this.priority = priority;
    }

    public void populate(Set<E> x ){

        for(E element: x){
            if( this.q.size() < this.fixedsize){
                this.q.add(element);
            }else{
                if( this.priority.compare(this.q.peek(),element)< 0 ){
                    this.q.poll();
                    this.q.add(element);
                }
            }
        }
    }

    public List<E> terminateToList(){
        ArrayList<E> x = new ArrayList<E>(this.fixedsize);

        while( this.q.size()>0){
            E y = this.q.poll();
            x.add(this.q.size()-1, y);
        }
        return x;
    }

}

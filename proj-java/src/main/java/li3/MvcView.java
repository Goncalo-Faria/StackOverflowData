package li3;

import java.awt.*;
import common.Pair;
import li3.TADCommunity;
import java.awt.event.ActionListener;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.List;
import java.util.Scanner;
import javax.swing.*;

public class MvcView extends JFrame {
    //interface gráfica do trabalho


    //geral
    private JButton calculateButton = new JButton("Result");
    private JTextField calcSolution = new JTextField(30);
    private JTextField numberid2  = new JTextField(10);
    private JTextField numberid1  = new JTextField(10);
    private JTextField info = new JTextField(20);
    private JTextField number  = new JTextField(10);
    private JTextField data_inicial = new JTextField(10);
    private JTextField data_final = new JTextField(10);

    //primeira interrogacao
    private JLabel interrogacao1 = new JLabel("Interrogação 1 :");

    //segunda interrogacao
    private JLabel interrogacao2 = new JLabel("Interrogação 2 :");

    //terceira interrogacao
    private JLabel interrogacao3 = new JLabel("Interrogação 3 :");

    //quarta interrogacao
    private JLabel interrogacao4 = new JLabel("Interrogação 4 :");

    //quinta interrogacao
    private JLabel interrogacao5 = new JLabel("Interrogação 5 :");

    //sexta interrogacao
    private JLabel interrogacao6 = new JLabel("Interrogação 6 :");

    //setima interrogacao
    private JLabel interrogacao7 = new JLabel("Interrogação 7 :");

    //oitava interrogacao
    private JLabel interrogacao8 = new JLabel("Interrogação 8 :");

    //nona interrogacao
    private JLabel interrogacao9 = new JLabel("Interrogação 9 :");

    //decima interrogacao
    private JLabel interrogacao10 = new JLabel("Interrogação 10 :");

    //decima primeira interrogacao
    private JLabel interrogacao11 = new JLabel("Interrogação 11 :");

    //decima segunda interrogacao
    private JLabel interrogacao12 = new JLabel("Interrogação 12 :");


    public MvcView(String x) {

        if (x.compareTo("1") == 0) {
            JPanel calcPanel = new JPanel();
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            this.setSize(1000, 200);
            Interrogacao1View(calcPanel);
        }

        if (x.compareTo("2") == 0) {
            JPanel calcPanel = new JPanel();
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            this.setSize(1000, 200);
            Interrogacao2View(calcPanel);
        }

        if (x.compareTo("3") == 0) {
            JPanel calcPanel = new JPanel();
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            this.setSize(1000, 200);
            Interrogacao3View(calcPanel);
        }

        if (x.compareTo("4") == 0) {
            JPanel calcPanel = new JPanel();
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            this.setSize(1000, 200);
            Interrogacao4View(calcPanel);
        }
        if (x.compareTo("5") == 0) {
            JPanel calcPanel = new JPanel();
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            this.setSize(1000, 200);
            Interrogacao5View(calcPanel);
        }
        if (x.compareTo("6") == 0) {
            JPanel calcPanel = new JPanel();
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            this.setSize(1000, 200);
            Interrogacao6View(calcPanel);
        }
        if (x.compareTo("7") == 0) {
            JPanel calcPanel = new JPanel();
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            this.setSize(1000, 200);
            Interrogacao7View(calcPanel);
        }
        if (x.compareTo("8") == 0) {
            JPanel calcPanel = new JPanel();
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            this.setSize(1000, 200);
            Interrogacao8View(calcPanel);
        }
        if (x.compareTo("9") == 0) {
            JPanel calcPanel = new JPanel();
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            this.setSize(1000, 200);
            Interrogacao9View(calcPanel);
        }
        if (x.compareTo("10") == 0) {
            JPanel calcPanel = new JPanel();
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            this.setSize(1000, 200);
            Interrogacao10View(calcPanel);
        }
        if (x.compareTo("11") == 0) {
            JPanel calcPanel = new JPanel();
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            this.setSize(1000, 200);
            Interrogacao11View(calcPanel);
        }

    }

    public void Interrogacao1View(JPanel calcPanel){
        calcPanel.add(interrogacao1);
        calcPanel.add(number);
        calcPanel.add(calculateButton);
        calcPanel.add(calcSolution);
        this.add(calcPanel);
    }
    public void Interrogacao2View(JPanel calcPanel){
        calcPanel.add(interrogacao2);
        calcPanel.add(number);
        calcPanel.add(calculateButton);
        calcPanel.add(calcSolution);
        this.add(calcPanel);
    }
    public void Interrogacao3View(JPanel calcPanel){
        calcPanel.add(interrogacao3);
        calcPanel.add(data_inicial);
        calcPanel.add(data_final);
        calcPanel.add(calculateButton);
        calcPanel.add(calcSolution);
        this.add(calcPanel);
    }
    public void Interrogacao4View(JPanel calcPanel){
        calcPanel.add(interrogacao4);
        calcPanel.add(info);
        calcPanel.add(data_inicial);
        calcPanel.add(data_final);
        calcPanel.add(calculateButton);
        calcPanel.add(calcSolution);
        this.add(calcPanel);
    }
    public void Interrogacao5View(JPanel calcPanel){
        calcPanel.add(interrogacao5);
        calcPanel.add(numberid1);
        calcPanel.add(calculateButton);
        calcPanel.add(calcSolution);
        this.add(calcPanel);
    }

    public void Interrogacao6View(JPanel calcPanel){
        calcPanel.add(interrogacao7);
        calcPanel.add(number);
        calcPanel.add(data_inicial);
        calcPanel.add(data_final);
        calcPanel.add(calculateButton);
        calcPanel.add(calcSolution);
        this.add(calcPanel);
    }
    public void Interrogacao7View(JPanel calcPanel){
        calcPanel.add(interrogacao7);
        calcPanel.add(number);
        calcPanel.add(data_inicial);
        calcPanel.add(data_final);
        calcPanel.add(calculateButton);
        calcPanel.add(calcSolution);
        this.add(calcPanel);
    }
    public void Interrogacao8View(JPanel calcPanel){
        calcPanel.add(interrogacao8);
        calcPanel.add(info);
        calcPanel.add(number);
        calcPanel.add(calculateButton);
        calcPanel.add(calcSolution);
        this.add(calcPanel);
    }
    public void Interrogacao9View(JPanel calcPanel){
        calcPanel.add(interrogacao9);
        calcPanel.add(numberid1);
        calcPanel.add(numberid2);
        calcPanel.add(number);
        calcPanel.add(calculateButton);
        calcPanel.add(calcSolution);
        this.add(calcPanel);
    }
    public void Interrogacao10View(JPanel calcPanel){
        calcPanel.add(interrogacao10);
        calcPanel.add(numberid1);
        calcPanel.add(calculateButton);
        calcPanel.add(calcSolution);
        this.add(calcPanel);
    }
    public void Interrogacao11View(JPanel calcPanel){
        calcPanel.add(interrogacao11);
        calcPanel.add(info);
        calcPanel.add(number);
        calcPanel.add(data_inicial);
        calcPanel.add(data_final);
        calcPanel.add(calculateButton);
        calcPanel.add(calcSolution);
        this.add(calcPanel);
    }

    public Long getNumberid1(){
        return Long.parseLong(numberid1.getText());
    }

    public Long getNumberid2(){
        return Long.parseLong(numberid2.getText());
    }

    public int getNumber(){
        return Integer.parseInt(number.getText());
    }

    public String getInfo(){
        return info.getText();
    }

    public LocalDate getData_inicial(){
        return LocalDate.parse(data_inicial.getText());
    }

    public LocalDate getData_final(){
        return LocalDate.parse(data_final.getText());
    }

    public void setLongSolution(Long x){
        calcSolution.setText(x.toString());
    }

    public void setPairSolution(Pair x){
        if(x.getFst() == null) calcSolution.setText("None");
        else calcSolution.setText(x.getFst().toString() + " " + x.getSnd().toString());
    }

    public void setListSolution(List x){

        calcSolution.setText(x.toString());
    }

    void addCalculateListener(ActionListener listenForCalcButton){

        calculateButton.addActionListener(listenForCalcButton);

    }

    // Open a popup that contains the error message passed

    void displayErrorMessage(String errorMessage){

        JOptionPane.showMessageDialog(this, errorMessage);

    }

}

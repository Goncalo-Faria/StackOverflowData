package view;

import java.awt.*;
import common.Pair;
import java.awt.event.ActionListener;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.List;
import java.util.Scanner;
import javax.swing.*;

/**
 * Teste para a classe MvcView.
 *
 * @author  Guilherme Viveiros e Gonçalo Faria
 * @version 1
 */

public class MvcView extends JFrame {
    // interface gráfica do trabalho
    private JPanel calcPanel;
    private JButton calculateButton = new JButton("Result");
    private JTextField calcSolution = new JTextField(30);
    private JTextField numberid2 = new JTextField(10);
    private JTextField numberid1 = new JTextField(10);
    private JTextField info = new JTextField(20);
    private JTextField number = new JTextField(10);
    private JTextField data_inicial = new JTextField(10);
    private JTextField data_final = new JTextField(10);

    /**
     * Construtor por omissão
     */
    public MvcView() {
        this.calcPanel = new JPanel();
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(1000, 200);

    }

    /**
     * Recebe o numero da interrogacao e inicializa a sua respetiva interface
     * @param String
     */
    public void setInterrogacaoViewer(String x) {
        try {
            switch (Integer.valueOf(x).intValue()) {
            case 0:
                this.Interrogacao0View(calcPanel);
                break;
            case 1:
                this.Interrogacao1View(calcPanel);
                break;
            case 2:
                this.Interrogacao2View(calcPanel);
                break;
            case 3:
                this.Interrogacao3View(calcPanel);
                break;
            case 4:
                this.Interrogacao4View(calcPanel);
                break;
            case 5:
                this.Interrogacao5View(calcPanel);
                break;
            case 6:
                this.Interrogacao6View(calcPanel);
                break;
            case 7:
                this.Interrogacao7View(calcPanel);
                break;
            case 8:
                this.Interrogacao8View(calcPanel);
                break;
            case 9:
                this.Interrogacao9View(calcPanel);
                break;
            case 10:
                this.Interrogacao10View(calcPanel);
                break;
            case 11:
                this.Interrogacao11View(calcPanel);
                break;
            case 12:
                this.Interrogacao12View(calcPanel);
                break;
            }
        } catch (Exception e) {
            System.out.println(e.toString());
        }
    }

    /**
     * Inicializa a interface para o load
     * @param calcPanel
     */
    public void Interrogacao0View(JPanel calcPanel) {
        calcPanel.add(new JLabel("load :"));
        calcPanel.add(this.info);
        calcPanel.add(this.calculateButton);
        calcPanel.add(this.calcSolution);
        this.add(calcPanel);
    }

    /**
     * Inicializa a interface para a interrogação 1
     * @param calcPanel
     */
    public void Interrogacao1View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 1 :"));
        calcPanel.add(this.number);
        calcPanel.add(this.calculateButton);
        calcPanel.add(this.calcSolution);
        this.add(calcPanel);
    }

    /**
     * Inicializa a interface para a interrogação 2
     * @param calcPanel
     */
    public void Interrogacao2View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 2 :"));
        calcPanel.add(this.number);
        calcPanel.add(this.calculateButton);
        calcPanel.add(this.calcSolution);
        this.add(calcPanel);
    }

    /**
     * Inicializa a interface para a interrogação 3
     * @param calcPanel
     */
    public void Interrogacao3View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 3 :"));
        calcPanel.add(this.data_inicial);
        calcPanel.add(this.data_final);
        calcPanel.add(this.calculateButton);
        calcPanel.add(this.calcSolution);
        this.add(calcPanel);
    }

    /**
     * Inicializa a interface para a interrogação 4
     * @param calcPanel
     */
    public void Interrogacao4View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 4 :"));
        calcPanel.add(this.info);
        calcPanel.add(this.data_inicial);
        calcPanel.add(this.data_final);
        calcPanel.add(this.calculateButton);
        calcPanel.add(this.calcSolution);
        this.add(calcPanel);
    }

    /**
     * Inicializa a interface para a interrogação 5
     * @param calcPanel
     */
    public void Interrogacao5View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 5 :"));
        calcPanel.add(this.numberid1);
        calcPanel.add(this.calculateButton);
        calcPanel.add(this.calcSolution);
        this.add(calcPanel);
    }

    /**
     * Inicializa a interface para a interrogação 6
     * @param calcPanel
     */
    public void Interrogacao6View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 6 :"));
        calcPanel.add(this.number);
        calcPanel.add(this.data_inicial);
        calcPanel.add(this.data_final);
        calcPanel.add(this.calculateButton);
        calcPanel.add(this.calcSolution);
        this.add(calcPanel);
    }

    /**
     * Inicializa a interface para a interrogação 7
     * @param calcPanel
     */
    public void Interrogacao7View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 7 :"));
        calcPanel.add(this.number);
        calcPanel.add(this.data_inicial);
        calcPanel.add(this.data_final);
        calcPanel.add(this.calculateButton);
        calcPanel.add(this.calcSolution);
        this.add(calcPanel);
    }

    /**
     * Inicializa a interface para a interrogação 8
     * @param calcPanel
     */
    public void Interrogacao8View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 8 :"));
        calcPanel.add(this.info);
        calcPanel.add(this.number);
        calcPanel.add(this.calculateButton);
        calcPanel.add(this.calcSolution);
        this.add(calcPanel);
    }

    /**
     * Inicializa a interface para a interrogação 9
     * @param calcPanel
     */
    public void Interrogacao9View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 9 :"));
        calcPanel.add(this.numberid1);
        calcPanel.add(this.numberid2);
        calcPanel.add(this.number);
        calcPanel.add(this.calculateButton);
        calcPanel.add(this.calcSolution);
        this.add(calcPanel);
    }

    /**
     * Inicializa a interface para a interrogação 10
     * @param calcPanel
     */
    public void Interrogacao10View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 10 :"));
        calcPanel.add(this.numberid1);
        calcPanel.add(this.calculateButton);
        calcPanel.add(this.calcSolution);
        this.add(calcPanel);
    }

    /**
     * Inicializa a interface para a interrogação 11
     * @param calcPanel
     */
    public void Interrogacao11View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 11 :"));
        calcPanel.add(this.number);
        calcPanel.add(this.data_inicial);
        calcPanel.add(this.data_final);
        calcPanel.add(this.calculateButton);
        calcPanel.add(this.calcSolution);
        this.add(calcPanel);
    }

    /**
     * Inicializa a interface para o clear
     * @param calcPanel
     */
    public void Interrogacao12View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Clear :"));
        calcPanel.add(this.calculateButton);
        calcPanel.add(this.calcSolution);
        this.add(calcPanel);
    }

    /**
     * Devolve um long recebida através da interface
     * @return
     */
    public Long getNumberid1() {
        return Long.parseLong(this.numberid1.getText());
    }

    /**
     * Devolve um long recebida através da interface
     * @return
     */
    public Long getNumberid2() {
        return Long.parseLong(this.numberid2.getText());
    }

    /**
     * Devolve um Integer recebida através da interface
     * @return
     */
    public int getNumber() {
        return Integer.parseInt(this.number.getText());
    }

    /**
     * Devolve uma String recebida através da interface(info digitado pelo utilizador)
     * @return
     */
    public String getInfo() {
        return this.info.getText();
    }

    /**
     * Devolve uma Data recebida através da interface
     * @return
     */
    public LocalDate getData_inicial() {
        return LocalDate.parse(this.data_inicial.getText());
    }

    /**
     * Devolve uma Data recebida através da interface
     * @return
     */
    public LocalDate getData_final() {
        return LocalDate.parse(this.data_final.getText());
    }

    /**
     * Atribui um Long na interface
     * @param Long
     * */
    public void setLongSolution(Long x) {
        this.calcSolution.setText(x.toString());
    }

    /**
     * Atribui uma String na interface
     * @param String
     * */
    public void setTextSolution(String x) {
        this.calcSolution.setText(x);
    }

    /**
     * Atribui uma Pair convertida em String na interface
     * @param Pair
     * */
    public void setPairSolution(Pair x) {
        if (x.getFst() == null)
            this.calcSolution.setText("None");
        else
            this.calcSolution.setText(x.getFst().toString() + " " + x.getSnd().toString());
    }

    /**
     * Atribui uma Lista convertida em String na interface
     * @param List
     * */
    public void setListSolution(List x) {

        this.calcSolution.setText(x.toString());
    }

    /**
     * Modifica a ação
     * @param ActionListener
     * */
    public void addCalculateListener(ActionListener listenForCalcButton) {

        this.calculateButton.addActionListener(listenForCalcButton);

    }

    // Open a popup that contains the error message passed

    /**
     * Imprime mensagem de erro
     * @param String
     * */
    public void displayErrorMessage(String errorMessage) {

        JOptionPane.showMessageDialog(this, errorMessage);

    }

}

package li3;

import java.awt.*;
import common.Pair;
import java.awt.event.ActionListener;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.List;
import java.util.Scanner;
import javax.swing.*;

public class MvcView extends JFrame {
    // interface gráfica do trabalho
    private JPanel calcPanel;

    public MvcView() {
        this.calcPanel = new JPanel();
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(1000, 200);

    }

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
            }
        } catch (Exception e) {
            System.out.println(e.toString());
        }
    }

    public void Interrogacao0View(JPanel calcPanel) {
        calcPanel.add(new JLabel("load :"));
        calcPanel.add(new JTextField(20));
        calcPanel.add(new JButton("Result"));
        calcPanel.add(new JTextField(30));
        this.add(calcPanel);
    }

    public void Interrogacao1View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 1 :"));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JButton("Result"));
        calcPanel.add(new JTextField(30));
        this.add(calcPanel);
    }

    public void Interrogacao2View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 2 :"));
        calcPanel.add(new JTextField(10);
        calcPanel.add(new JButton("Result"));
        calcPanel.add(new JTextField(30));
        this.add(calcPanel);
    }

    public void Interrogacao3View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 3 :"));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JButton("Result"));
        calcPanel.add(new JTextField(30));
        this.add(calcPanel);
    }

    public void Interrogacao4View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 4 :"));
        calcPanel.add(new JTextField(20));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JButton("Result"));
        calcPanel.add(new JTextField(30));
        this.add(calcPanel);
    }

    public void Interrogacao5View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 5 :"));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JButton("Result"));
        calcPanel.add(new JTextField(30));
        this.add(calcPanel);
    }

    public void Interrogacao6View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 6 :"));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JButton("Result"));
        calcPanel.add(new JTextField(30));
        this.add(calcPanel);
    }

    public void Interrogacao7View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 7 :"));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JButton("Result"));
        calcPanel.add(new JTextField(30));
        this.add(calcPanel);
    }

    public void Interrogacao8View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 8 :"));
        calcPanel.add(new JTextField(20));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JButton("Result"));
        calcPanel.add(new JTextField(30));
        this.add(calcPanel);
    }

    public void Interrogacao9View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 9 :"));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JTextField(10)id2);
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JButton("Result"));
        calcPanel.add(new JTextField(30));
        this.add(calcPanel);
    }

    public void Interrogacao10View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 10 :"));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JButton("Result"));
        calcPanel.add(new JTextField(30));
        this.add(calcPanel);
    }

    public void Interrogacao11View(JPanel calcPanel) {
        calcPanel.add(new JLabel("Interrogação 11 :"));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JTextField(10));
        calcPanel.add(new JButton("Result"));
        calcPanel.add(new JTextField(30));
        this.add(calcPanel);
    }

    public Long getNumberid1() {
        return Long.parseLong(new JTextField(10).getText());
    }

    public Long getNumberid2() {
        return Long.parseLong(new JTextField(10)id2.getText());
    }

    public int getNumber() {
        return Integer.parseInt(new JTextField(10).getText());
    }

    public String getInfo() {
        return new JTextField(20).getText();
    }

    public LocalDate getData_inicial() {
        return LocalDate.parse(new JTextField(10).getText());
    }

    public LocalDate getData_final() {
        return LocalDate.parse(new JTextField(10).getText());
    }

    public void setLongSolution(Long x) {
        new JTextField(30).setText(x.toString());
    }

    public void setPairSolution(Pair x) {
        if (x.getFst() == null)
            new JTextField(30).setText("None");
        else
            new JTextField(30).setText(x.getFst().toString() + " " + x.getSnd().toString());
    }

    public void setListSolution(List x) {

        new JTextField(30).setText(x.toString());
    }

    void addCalculateListener(ActionListener listenForCalcButton) {

        new JButton("Result").addActionListener(listenForCalcButton);

    }

    // Open a popup that contains the error message passed

    void displayErrorMessage(String errorMessage) {

        JOptionPane.showMessageDialog(this, errorMessage);

    }

}

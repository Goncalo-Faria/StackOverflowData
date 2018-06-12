package controller;

import li3.TADCommunity;
import view.MvcView;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.time.LocalDate;

public class MvcController implements ActionListener {
    // Faz com que o View e o Model(TadCommunity) trabalhem em sintonia
    private MvcView theView;
    private TADCommunity theModel;
    private int currentQuerie;

    public MvcController(TADCommunity theModel) {

        this.theView = new MvcView();
        this.theModel = theModel;
    }

    public void setInterrogacao(String x) {
        this.hide();
        this.theView = new MvcView();
        this.theView.setInterrogacaoViewer(x);
        this.currentQuerie = Integer.valueOf(x).intValue();
        try {
            switch (this.currentQuerie) {
            case 0:
                this.theView.addCalculateListener(this);
                break;
            case 1:
                this.theView.addCalculateListener(this);
                break;
            case 2:
                this.theView.addCalculateListener(this);
                break;
            case 3:
                this.theView.addCalculateListener(this);
                break;
            case 4:
                this.theView.addCalculateListener(this);
                break;
            case 5:
                this.theView.addCalculateListener(this);
                break;
            case 6:
                this.theView.addCalculateListener(this);
                break;
            case 7:
                this.theView.addCalculateListener(this);
                break;
            case 8:
                this.theView.addCalculateListener(this);
                break;
            case 9:
                this.theView.addCalculateListener(this);
                break;
            case 10:
                this.theView.addCalculateListener(this);
                break;
            case 11:
                this.theView.addCalculateListener(this);
                break;
            }
        } catch (Exception e) {
            System.out.println(e.toString());
        }
    }

    public void show() {
        theView.setVisible(true);
    }

    public void hide() {
        theView.setVisible(false);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        switch (currentQuerie) {
        case 0:Interrogacao0();
            break;
        case 1:Interrogacao1();
            break;
        case 2:Interrogacao2();
            break;
        case 3:Interrogacao3();
            break;
        case 4:Interrogacao4();
            break;
        case 5:Interrogacao5();
            break;
        case 6:Interrogacao6();
            break;
        case 7:Interrogacao7();
            break;
        case 8:Interrogacao8();
            break;
        case 9:Interrogacao9();
            break;
        case 10:Interrogacao10();
            break;
        case 11:Interrogacao11();
            break;
        }
    }

    private void Interrogacao0() {
        String info;
        try {
            info = theView.getInfo();
            theModel.load(info);
            theView.setTextSolution("Load efetuado com sucesso!\n");
        }

        catch (NumberFormatException ex) {
            System.out.println(ex);
            theView.displayErrorMessage("You Need to Enter 1 Number");
        }
    }

    private void Interrogacao1() {
        long firstNumber = 0;
        try {

            firstNumber = theView.getNumber();
            theView.setPairSolution(theModel.infoFromPost(firstNumber));
        } catch (NumberFormatException ex) {
            System.out.println(ex);
            theView.displayErrorMessage("You Need to Enter 1 Number");
        }
    }

    private void Interrogacao2() {
        int firstNumber = 0;

        try {
            firstNumber = theView.getNumber();

            theView.setListSolution(theModel.topMostActive(firstNumber));
        } catch (NumberFormatException ex) {
            System.out.println(ex);
            theView.displayErrorMessage("You Need to Enter 1 Integers");
        }
    }

    private void Interrogacao3() {
        LocalDate begin;
        LocalDate end;

        try {
            begin = theView.getData_inicial();
            end = theView.getData_final();
            theView.setPairSolution(theModel.totalPosts(begin, end));
        }

        catch (NumberFormatException ex) {
            System.out.println(ex);
            theView.displayErrorMessage("You Need to Enter 2 Datas");
        }
    }

    private void Interrogacao4() {
        LocalDate begin;
        LocalDate end;
        String info;

        try {
            info = theView.getInfo();
            begin = theView.getData_inicial();
            end = theView.getData_final();
            theView.setListSolution(theModel.questionsWithTag(info, begin, end));
        }

        catch (NumberFormatException ex) {
            System.out.println(ex);
            theView.displayErrorMessage("You Need to Enter 2 Datas and 1 Tag");
        }
    }

    private void Interrogacao5() {
        Long firstNumber;
            try {
                firstNumber = theView.getNumberid1();
                theView.setPairSolution(theModel.getUserInfo(firstNumber));
            }

            catch (NumberFormatException ex) {
                System.out.println(ex);
                theView.displayErrorMessage("You Need to Enter 1 Number");
            }
    }

    private void Interrogacao6() {
        LocalDate begin;
            LocalDate end;
            int firstNumber;

            try {
                firstNumber = theView.getNumber();
                begin = theView.getData_inicial();
                end = theView.getData_final();
                theView.setListSolution(theModel.mostVotedAnswers(firstNumber, begin, end));

            }

            catch (NumberFormatException ex) {
                System.out.println(ex);
                theView.displayErrorMessage("You Need to Enter 2 Datas and 1 Number");
            }
    }

    private void Interrogacao7() {
        LocalDate begin;
            LocalDate end;
            int firstNumber;

            try {
                firstNumber = theView.getNumber();
                begin = theView.getData_inicial();
                end = theView.getData_final();
                theView.setListSolution(theModel.mostAnsweredQuestions(firstNumber, begin, end));
            } catch (NumberFormatException ex) {
                System.out.println(ex);
                theView.displayErrorMessage("You Need to Enter 2 Datas and 1 Number");
            }
    }

    private void Interrogacao8() {
        String info;
            int firstNumber;

            try {
                firstNumber = theView.getNumber();
                info = theView.getInfo();
                theView.setListSolution(theModel.containsWord(firstNumber, info));
            } catch (NumberFormatException ex) {
                System.out.println(ex);
                theView.displayErrorMessage("You Need to Enter 1 word and 1 Number");
            }
    }

    private void Interrogacao9() {
        Long id1;
            Long id2;
            int firstNumber;

            try {
                id1 = theView.getNumberid1();
                id2 = theView.getNumberid2();
                firstNumber = theView.getNumber();
                theView.setListSolution(theModel.bothParticipated(firstNumber, id1, id2));
            } catch (NumberFormatException ex) {
                System.out.println(ex);
                theView.displayErrorMessage("You Need to Enter 2 Ids and 1 Number");
            }
    }

    private void Interrogacao10() {
        Long number;

        try {
            number = theView.getNumberid1();
            theView.setLongSolution(theModel.betterAnswer(number));
        } catch (NumberFormatException ex) {
            System.out.println(ex);
            theView.displayErrorMessage("You Need to Enter 1 Number");
        }
    }

    private void Interrogacao11() {
        LocalDate begin;
            LocalDate end;
            int firstNumber;

            try {
                firstNumber = theView.getNumber();
                begin = theView.getData_inicial();
                end = theView.getData_final();
                theView.setListSolution(theModel.mostUsedBestRep(firstNumber, begin, end));
            } catch (NumberFormatException ex) {
                System.out.println(ex);
                theView.displayErrorMessage("You Need to Enter 1 Number and 2 Data");
            }
    }

}

package controller;

import li3.TADCommunity;
import view.MvcView;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.time.LocalDate;

/**
 * Teste para a classe MvcController.
 *
 * @author  Guilherme Viveiros e Gonçalo Faria
 * @version 1
 */
public class MvcController implements ActionListener {
    // Faz com que o View e o Model(TadCommunity) trabalhem em sintonia
    private MvcView theView;
    private TADCommunity theModel;
    private int currentQuerie;

    /**
     * Construtor por parametro
     * @param TADCommunity
     */
    public MvcController(TADCommunity theModel) {

        this.theView = new MvcView();
        this.theModel = theModel;
    }

    /**
     * Recebe o numero da interrogacao , inicializando-a no View
     * @param String
     */
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
            case 12:
                this.theView.addCalculateListener(this);
                break;
            }
        } catch (Exception e) {
            System.out.println(e.toString());
        }
    }

    public void show() {
        this.theView.setVisible(true);
    }

    public void hide() {
        this.theView.setVisible(false);
    }

    /**
     * Inicializa a respetiva Interrogação
     * @param Action
     */
    public void actionPerformed(ActionEvent e) {
        switch (this.currentQuerie) {
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
        case 12:clear();
        }
    }

    /**
     * Executa o load
     */
    private void Interrogacao0() {
        String info;
        try {
            info = this.theView.getInfo();
            this.theModel.load(info);
            this.theView.setTextSolution("Load efetuado com sucesso!\n");
        }

        catch (NumberFormatException ex) {
            System.out.println(ex);
            this.theView.displayErrorMessage("You Need to Enter 1 Number");
        }
    }

    /**
     * Executa a Interrogacao1 através dos parametros recebidos na interface
     */
    private void Interrogacao1() {
        long firstNumber = 0;
        try {

            firstNumber = this.theView.getNumber();
            this.theView.setPairSolution(this.theModel.infoFromPost(firstNumber));
        } catch (NumberFormatException ex) {
            System.out.println(ex);
            this.theView.displayErrorMessage("You Need to Enter 1 Number");
        }
    }

    /**
     * Executa a Interrogacao2 através dos parametros recebidos na interface
     */
    private void Interrogacao2() {
        int firstNumber = 0;

        try {
            firstNumber = this.theView.getNumber();

            this.theView.setListSolution(this.theModel.topMostActive(firstNumber));
        } catch (NumberFormatException ex) {
            System.out.println(ex);
            this.theView.displayErrorMessage("You Need to Enter 1 Integers");
        }
    }

    /**
     * Executa a Interrogacao3 através dos parametros recebidos na interface
     */
    private void Interrogacao3() {
        LocalDate begin;
        LocalDate end;

        try {
            begin = this.theView.getData_inicial();
            end = this.theView.getData_final();
            this.theView.setPairSolution(this.theModel.totalPosts(begin, end));
        }

        catch (NumberFormatException ex) {
            System.out.println(ex);
            this.theView.displayErrorMessage("You Need to Enter 2 Datas");
        }
    }

    /**
     * Executa a Interrogacao4 através dos parametros recebidos na interface
     */
    private void Interrogacao4() {
        LocalDate begin;
        LocalDate end;
        String info;

        try {
            info = this.theView.getInfo();
            begin = this.theView.getData_inicial();
            end = this.theView.getData_final();
            this.theView.setListSolution(this.theModel.questionsWithTag(info, begin, end));
        }

        catch (NumberFormatException ex) {
            System.out.println(ex);
            this.theView.displayErrorMessage("You Need to Enter 2 Datas and 1 Tag");
        }
    }

    /**
     * Executa a Interrogacao5 através dos parametros recebidos na interface
     */
    private void Interrogacao5() {
        Long firstNumber;
            try {
                firstNumber = this.theView.getNumberid1();
                this.theView.setPairSolution(this.theModel.getUserInfo(firstNumber));
            }

            catch (NumberFormatException ex) {
                System.out.println(ex);
                this.theView.displayErrorMessage("You Need to Enter 1 Number");
            }
    }

    /**
     * Executa a Interrogacao6 através dos parametros recebidos na interface
     */
    private void Interrogacao6() {
        LocalDate begin;
            LocalDate end;
            int firstNumber;

            try {
                firstNumber = this.theView.getNumber();
                begin = this.theView.getData_inicial();
                end = this.theView.getData_final();
                this.theView.setListSolution(this.theModel.mostVotedAnswers(firstNumber, begin, end));

            }

            catch (NumberFormatException ex) {
                System.out.println(ex);
                this.theView.displayErrorMessage("You Need to Enter 2 Datas and 1 Number");
            }
    }

    /**
     * Executa a Interrogacao7 através dos parametros recebidos na interface
     */
    private void Interrogacao7() {
        LocalDate begin;
            LocalDate end;
            int firstNumber;

            try {
                firstNumber =this.theView.getNumber();
                begin = this.theView.getData_inicial();
                end = this.theView.getData_final();
                this.theView.setListSolution(this.theModel.mostAnsweredQuestions(firstNumber, begin, end));
            } catch (NumberFormatException ex) {
                System.out.println(ex);
                this.theView.displayErrorMessage("You Need to Enter 2 Datas and 1 Number");
            }
    }

    /**
     * Executa a Interrogacao8 através dos parametros recebidos na interface
     */
    private void Interrogacao8() {
        String info;
            int firstNumber;

            try {
                firstNumber = this.theView.getNumber();
                info = this.theView.getInfo();
                this.theView.setListSolution(this.theModel.containsWord(firstNumber, info));
            } catch (NumberFormatException ex) {
                System.out.println(ex);
                this.theView.displayErrorMessage("You Need to Enter 1 word and 1 Number");
            }
    }

    /**
     * Executa a Interrogacao9 através dos parametros recebidos na interface
     */
    private void Interrogacao9() {
        Long id1;
            Long id2;
            int firstNumber;

            try {
                id1 = this.theView.getNumberid1();
                id2 = this.theView.getNumberid2();
                firstNumber = this.theView.getNumber();
                this.theView.setListSolution(this.theModel.bothParticipated(firstNumber, id1, id2));
            } catch (NumberFormatException ex) {
                System.out.println(ex);
                this.theView.displayErrorMessage("You Need to Enter 2 Ids and 1 Number");
            }
    }

    /**
     * Executa a Interrogacao10 através dos parametros recebidos na interface
     */
    private void Interrogacao10() {
        Long number;

        try {
            number = this.theView.getNumberid1();
            this.theView.setLongSolution(this.theModel.betterAnswer(number));
        } catch (NumberFormatException ex) {
            System.out.println(ex);
            this.theView.displayErrorMessage("You Need to Enter 1 Number");
        }
    }

    /**
     * Executa a Interrogacao11 através dos parametros recebidos na interface
     */
    private void Interrogacao11() {
        LocalDate begin;
            LocalDate end;
            int firstNumber;

            try {
                firstNumber = this.theView.getNumber();
                begin = this.theView.getData_inicial();
                end = this.theView.getData_final();
                this.theView.setListSolution(this.theModel.mostUsedBestRep(firstNumber, begin, end));
            } catch (NumberFormatException ex) {
                System.out.println(ex);
                this.theView.displayErrorMessage("You Need to Enter 1 Number and 2 Data");
            }
    }

    /**
     * Executa o clear
     */
    private void clear() {
        try {
            this.theModel.clear();
            this.theView.setTextSolution("Delete efetuado com sucesso!\n");
        }

        catch (NumberFormatException ex) {
            System.out.println(ex);
            this.theView.displayErrorMessage("You Need to Enter 1 Number");
        }
    }

}

package li3;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.time.LocalDate;

public class MvcController {
    // Faz com que o View e o Model(TadCommunity) trabalhem em sintonia
    private MvcView theView;
    private TADCommunity theModel;

    public MvcController(TADCommunity theModel) {

        this.theView = new MvcView();
        this.theModel = theModel;
    }

    public void setInterrogacao(String x) {

        this.theView.setInterrogacaoViewer(x);
        try {
            switch (Integer.valueOf(x).intValue()) {
            case 0:
                this.theView.addCalculateListener(new Interrogacao0());
                break;
            case 1:
                this.theView.addCalculateListener(new Interrogacao1());
                break;
            case 2:
                this.theView.addCalculateListener(new Interrogacao2());
                break;
            case 3:
                this.theView.addCalculateListener(new Interrogacao3());
                break;
            case 4:
                this.theView.addCalculateListener(new Interrogacao4());
                break;
            case 5:
                this.theView.addCalculateListener(new Interrogacao5());
                break;
            case 6:
                this.theView.addCalculateListener(new Interrogacao6());
                break;
            case 7:
                this.theView.addCalculateListener(new Interrogacao7());
                break;
            case 8:
                this.theView.addCalculateListener(new Interrogacao8());
                break;
            case 9:
                this.theView.addCalculateListener(new Interrogacao9());
                break;
            case 10:
                this.theView.addCalculateListener(new Interrogacao10());
                break;
            case 11:
                this.theView.addCalculateListener(new Interrogacao11());
                break;
            }
        } catch (Exception e) {
            System.out.println(e.toString());
        }




        if (x.equals("0")) {
            this.theView.addCalculateListener(new Interrogacao0());
        }

        if (x.equals("1")) {
            this.theView.addCalculateListener(new Interrogacao1());
        }
        if (x.equals("2")) {
            this.theView.addCalculateListener(new Interrogacao2());
        }
        if (x.equals("3")) {
            this.theView.addCalculateListener(new Interrogacao3());
        }
        if (x.equals("4")) {
            this.theView.addCalculateListener(new Interrogacao4());
        }
        if (x.equals("5")) {
            this.theView.addCalculateListener(new Interrogacao5());
        }
        if (x.equals("6")) {
            this.theView.addCalculateListener(new Interrogacao6());
        }
        if (x.equals("7")) {
            this.theView.addCalculateListener(new Interrogacao7());
        }
        if (x.equals("8")) {
            this.theView.addCalculateListener(new Interrogacao8());
        }
        if (x.equals("9")) {
            this.theView.addCalculateListener(new Interrogacao9());
        }
        if (x.equals("10")) {
            this.theView.addCalculateListener(new Interrogacao10());
        }
        if (x.equals("11")) {
            this.theView.addCalculateListener(new Interrogacao11());
        }
    }

    public void show() {
        theView.setVisible(true);
    }

    public void hide() {
        theView.setVisible(false);
    }

    public class Interrogacao0 implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            System.out.println("aa");
            String info;

            try {
                info = theView.getInfo();
                theModel.load(info);
            }

            catch (NumberFormatException ex) {
                System.out.println(ex);
                theView.displayErrorMessage("You Need to Enter 1 Number");
            }
        }
    }

    // Interrogação 1
    public class Interrogacao1 implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            System.out.println("aa");
            long firstNumber = 0;
            try {

                firstNumber = theView.getNumber();
                theView.setPairSolution(theModel.infoFromPost(firstNumber));
            }

            catch (NumberFormatException ex) {
                System.out.println(ex);
                theView.displayErrorMessage("You Need to Enter 1 Number");
            }
        }
    }

    // Interrogação 2
    public class Interrogacao2 implements ActionListener {
        public void actionPerformed(ActionEvent e) {

            int firstNumber = 0;

            try {
                firstNumber = theView.getNumber();

                theView.setListSolution(theModel.topMostActive(firstNumber));
            } catch (NumberFormatException ex) {
                System.out.println(ex);
                theView.displayErrorMessage("You Need to Enter 1 Integers");
            }
        }
    }

    // Interrogação 3
    public class Interrogacao3 implements ActionListener {
        public void actionPerformed(ActionEvent e) {

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
    }

    // Interrogação 4
    public class Interrogacao4 implements ActionListener {
        public void actionPerformed(ActionEvent e) {

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
    }

    // Interrogação 5
    public class Interrogacao5 implements ActionListener {
        public void actionPerformed(ActionEvent e) {

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
    }

    // Interrogação 6
    public class Interrogacao6 implements ActionListener {

        public void actionPerformed(ActionEvent e) {

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
    }

    // Interrogação 7
    public class Interrogacao7 implements ActionListener {
        public void actionPerformed(ActionEvent e) {

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
    }

    // Interrogação 8
    public class Interrogacao8 implements ActionListener {
        public void actionPerformed(ActionEvent e) {

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
    }

    // Interrogação 9
    public class Interrogacao9 implements ActionListener {
        public void actionPerformed(ActionEvent e) {

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
    }

    // Interrogação 10
    public class Interrogacao10 implements ActionListener {
        public void actionPerformed(ActionEvent e) {

            Long number;

            try {
                number = theView.getNumberid1();
                theView.setLongSolution(theModel.betterAnswer(number));
            } catch (NumberFormatException ex) {
                System.out.println(ex);
                theView.displayErrorMessage("You Need to Enter 1 Number");
            }
        }
    }

    // Interrogação 11
    public class Interrogacao11 implements ActionListener {
        public void actionPerformed(ActionEvent e) {

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
}

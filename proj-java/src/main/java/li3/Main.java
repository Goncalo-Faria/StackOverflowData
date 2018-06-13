package li3;

import common.MyLog;
import common.Pair;
import engine.Comunidade;
import controller.MvcController;

import java.time.LocalDate;
import java.time.Month;
import java.util.List;
import java.util.Scanner;

public class Main {

    // irá tratar de por o Model(Tad Community , O View e o Controller a funcionar)

    public static void main(String[] args) {
        Scanner x = new Scanner(System.in);
        String check;

        MvcController theController = new MvcController(new Comunidade());

        do {

            System.out.println(
                    "Digite o numero da interrogação que pretende testar.\nCaso pretenda parar digite 'stop'.");
            check = x.next();
            theController.hide();
            if (!check.contains("stop")) {
                theController.setInterrogacao(check);
                theController.show();
            } else {
                break;
            }
        } while (true);
        System.out.println("Program executado com sucesso.");
        System.exit(0);

    }

}

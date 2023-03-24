package org.project.poo;
import java.util.Scanner;

public class Menu {
        private static Scanner read = new Scanner(System.in);

        public static int chooseAccount(Account[] acounts) {
                int chosenOpt = 0;

                System.out.println("0) Criar nova conta");
                
                for(int i = 1; i <= acounts[0].getAccountAmount(); i++)
                        System.out.printf("%d) Conta %d\n", i, i);
                
                System.out.print("> ");
                chosenOpt = read.nextInt();
                chosenOpt--;

                if(chosenOpt == -1) {
                        chosenOpt = acounts[0].getAccountNum();
                        acounts[chosenOpt] = new Account();
                }

                return chosenOpt;
        }

        public static int mainMenu() {
                System.out.print(  "0) Voltar\n"                       +
                                   "1) Setar nome\n"                   +
                                   "2) Setar saldo\n"                  +
                                   "3) Mostrar informações da conta\n" +
                                   "4) Mostrar quantidade de contas\n" +
                                   "5) Depositar dinheiro\n"           +
                                   "6) Sacar dinheiro\n"               +
                                   "> ");

                return read.nextInt();
        }

        public static boolean verifyUserInput(Account account, int option) {
                switch(option) {
                        case 0:
                                return false;
                        case 1:
                                System.out.print("Digite um nome: ");
                                account.setName(read.next());
                                break;
                        case 2:
                                System.out.print("Digite um saldo: ");
                                account.setBalance(read.nextDouble());
                                break;
                        case 3:
                                System.out.print("Nome: " +    account.getName() +       "\n" +
                                                 "Conta: " +   account.getAccountNum() + "\n" +
                                                 "Agência: " + account.getAgency() +     "\n" + 
                                                 "Saldo: " +   account.getBalance() +    "\n");
                                break;
                        case 4:
                                System.out.println("Quantidade: " + account.getAccountAmount());
                                break;
                        case 5: 
                                System.out.print("Digite um valor: ");
                                account.depositCash(read.nextDouble());
                                break;
                        case 6:
                                System.out.println("Digite um valor: ");
                                account.withdrawCash(read.nextDouble());
                                break;
                        default:
                                System.out.println("Entrada inválida!");
                }

                return true;
        }
}

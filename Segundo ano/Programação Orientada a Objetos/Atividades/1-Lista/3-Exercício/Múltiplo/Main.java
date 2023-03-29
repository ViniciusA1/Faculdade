import java.util.Scanner;

public class Main {
        public static void main(String[] args) {
                int firstNum, secondNum;
                Scanner read = new Scanner(System.in);

                firstNum = read.nextInt();
                secondNum = read.nextInt();

                checkDivision(firstNum, secondNum);
                checkDivision(secondNum, firstNum);

                read.close();
        }

        public static void checkDivision(int n1, int n2) {
                System.out.printf(n1 % n2 != 0 ? "%d não é múltiplo de %d\n" : 
                                   "%d é múltiplo de %d\n", n1, n2);
        }
}

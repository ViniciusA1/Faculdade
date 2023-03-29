import java.util.Scanner;

public class Main {
        private static final int AMOUNT = 3;

        public static void main(String[] args) {
                Scanner read = new Scanner(System.in);
                int[] number = new int[AMOUNT];

                for(int i = 0; i < AMOUNT; i++)
                        number[i] = read.nextInt();

                System.out.println("Soma: " + sum(number)           + "\n" +
                                   "Média: " + average(number)      + "\n" +
                                   "Produto: " + product(number)    + "\n" +
                                   "Maior: " + highestValue(number) + "\n" +
                                   "Menor: " + lowestValue(number));

                read.close();
        }

        public static int sum(int[] number) {
                int sum = 0;

                for(int i = 0; i < AMOUNT; i++)
                        sum += number[i];

                return sum;
        }

        public static int average(int[] number) {
                return (sum(number) / AMOUNT);
        }

        public static int product(int[] number) {
                int result = 1;

                for(int i = 0; i < AMOUNT; i++)
                        result *= number[i];
                
                return result;
        }

        public static int highestValue(int[] number) {
                int highest = number[0];

                for(int i = 0; i < AMOUNT; i++) {
                        if(number[i] > highest)
                                highest = number[i];
                }

                return highest;
        }

        public static int lowestValue(int[] number) {
                int lowest = number[0];

                for(int i = 0; i < AMOUNT; i++) {
                        if(number[i] < lowest)
                                lowest = number[i];
                }

                return lowest;
        }
}

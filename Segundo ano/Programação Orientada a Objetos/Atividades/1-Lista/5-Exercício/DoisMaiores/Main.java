import java.util.Scanner;

public class Main {
        private static final int MAX = 15;

        public static void main(String[] args) {
                Scanner read = new Scanner(System.in);
                double[] numbers = new double[MAX];

                for(int i = 0; i < MAX; i++)
                        numbers[i] = read.nextDouble();

                highestNumbers(numbers);

                read.close();
        }

        public static void highestNumbers(double[] number) {
                double highest = number[0], prev = 0;
                
                for(int i = 0; i < MAX; i++) {
                        if(number[i] > highest) {
                                prev = highest;
                                highest = number[i];
                        }
                }

                System.out.printf("Maior número: %.2f\n" +
                                  "Segundo maior número: %.2f\n",
                                  highest, prev);
        }
}

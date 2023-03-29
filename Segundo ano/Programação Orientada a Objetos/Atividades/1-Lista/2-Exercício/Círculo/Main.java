import java.util.Scanner;

public class Main {
        public static void main(String[] args) {
                Scanner read = new Scanner(System.in);
                double radius;

                radius = read.nextDouble();

                System.out.printf("Diâmetro: %.2f\n" + "Área: %.2f\n" + "Circunferência: %.2f\n",
                                  2*radius, Math.PI * (radius*radius), 2*Math.PI*radius);

                read.close();
        }
}

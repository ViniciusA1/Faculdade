import java.util.Scanner;

public class Main {
        public static void main(String[] args) {
                Scanner read = new Scanner(System.in);
                char input;

                input = read.next().charAt(0);

                System.out.printf("%d\n", (int) input);

                read.close();
        }
}

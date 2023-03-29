import java.util.Scanner;

public class Main {
        private static final float BASE = 200;

        public static void main(String[] args) {
                Scanner read = new Scanner(System.in);
                float sales = 0;

                while(true) {
                        System.out.print("Digite o valor da venda: ");
                        sales = read.nextFloat();
                        
                        if(sales == -1)
                                break;
                        
                        System.out.println("Salário = " + (BASE + 0.09 * sales));
                }

                read.close();
        }
}

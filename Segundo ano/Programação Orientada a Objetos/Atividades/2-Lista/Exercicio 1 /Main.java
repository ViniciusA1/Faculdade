import java.util.Scanner;

public class Main {
        private final static Scanner read = new Scanner(System.in);

        public static void main(String[] args) {
                int[] tempo = new int[3];

                getDados(tempo, 1);
                Tempo tempo1 = new Tempo(tempo[0], tempo[1], tempo[2]);
                getDados(tempo, 2);
                Tempo tempo2 = new Tempo(tempo[0], tempo[1], tempo[2]);

                tempo1.imprimirDados();
                tempo2.imprimirDados();
                //tempo1.somar(tempo2);
                tempo1.imprimirDados();
                tempo1.subtrair(tempo2);
                tempo1.imprimirDados();
        }

        public static void getDados(int[] tempo, int qtd) {
                System.out.println("Tempo " + qtd);
                System.out.print("Horas: ");
                tempo[0] = read.nextInt();
                System.out.print("Minutos: ");
                tempo[1] = read.nextInt();
                System.out.print("Segundos: ");
                tempo[2] = read.nextInt();
        }
}

import java.util.Scanner;

public class Fracao {
        private int numerador;
        private int denominador;

        public Fracao(int numerador, int denominador) {
                this.numerador = numerador;
                this.denominador = verificaInput(denominador);
                simplificar();
        }

        private int verificaInput(int input) {
                Scanner read = new Scanner(System.in);
                
                while(input <= 0) {
                        System.out.print("Valor de denominador inválido! Digite outro: ");
                        input = read.nextInt();
                }

                read.close();
                return input;
        }

        public int getNumerador() {
                return numerador;
        }

        public int getDenominador() {
                return denominador;
        }

        public Fracao somar(Fracao fracao) {
                return duplaOperacao(fracao, 1);
        }

        public Fracao subtrair(Fracao fracao) { 
                return duplaOperacao(fracao, -1);
        }

        private Fracao duplaOperacao(Fracao fracaoAux, int signal) {
                Fracao resultante;

                int denomResultante = denominador * fracaoAux.getDenominador();
                int numResultante = ((denomResultante / denominador) * numerador) + 
                                    signal * ((denomResultante / fracaoAux.getDenominador()) *
                                    fracaoAux.getNumerador());

                resultante = new Fracao(numResultante, denomResultante);
                resultante.simplificar();

                return resultante;
        }

        public Fracao multiplicar(Fracao fracao) {
                Fracao resultante;
                
                resultante = new Fracao(numerador * fracao.getNumerador(), 
                                denominador * fracao.getDenominador());
                resultante.simplificar();

                return resultante;
        }

        public Fracao dividir(Fracao fracao) {
                Fracao resultante;

                resultante = new Fracao(numerador * fracao.getDenominador(), 
                                denominador * fracao.getNumerador());
                resultante.simplificar();

                return resultante;
        }

        private void simplificar() {
                int mdc = Math.abs(numerador > denominador ? 
                                   mdc(numerador, denominador) : 
                                   mdc(denominador, numerador));
                
                numerador /= mdc;
                denominador /= mdc;
        }

        private int mdc(int x, int y) {
                int aux;

                while(y != 0) {
                        aux = x % y;
                        x = y;
                        y = aux;
                }

                return x;
        }

        public void imprimir() {
                System.out.printf(" %d\n-", numerador);
                int length = (int) Math.max(Math.log10(numerador),
                                            Math.log10(denominador)) + 1;
                for(int i = 0; i < length; i++)
                        System.out.print("-");
                System.out.printf("-\n %d\n", denominador);
        }
}

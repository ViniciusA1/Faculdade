public class Main {
        public static void main(String[] args) {
                Fracao fracao1 = new Fracao(1, 2);
                System.out.println("Fração 1:");
                fracao1.imprimir();
                
                Fracao fracao2 = new Fracao(2, 3);
                System.out.println("\nFração 2:");
                fracao2.imprimir();

                Fracao resultado = fracao1.somar(fracao2);
                System.out.println("\nSoma:");
                resultado.imprimir();

                resultado = fracao1.subtrair(fracao2);
                System.out.println("\nSubtração:");
                resultado.imprimir();

                resultado = fracao1.multiplicar(fracao2);
                System.out.println("\nMultiplicação:");
                resultado.imprimir();

                resultado = fracao1.dividir(fracao2);
                System.out.println("\nDivisão:");
                resultado.imprimir();
        }
}

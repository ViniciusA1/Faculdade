public class Main {
        public static void main(String[] args) {
                int[] vetor1 = {1, 2, 3};
                int[] vetor2 = {4, 5, 6};
                int[] vetorSoma = Vetor.somar(vetor1, vetor2);

                if(vetorSoma == null) return;

                Vetor.imprimir(vetorSoma);

                double[] vec1 = {1.5, 2.5, 3.5};
                double[] vec2 = {4.5, 5.5, 6.5};
                double[] vecSoma = Vetor.somar(vec1, vec2);

                if(vecSoma == null) return;

                Vetor.imprimir(vecSoma);
        }
}

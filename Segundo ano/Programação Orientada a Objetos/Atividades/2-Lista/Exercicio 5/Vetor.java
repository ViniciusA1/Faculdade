public class Vetor {
        public static int[] somar(int[] x, int[] y) {
                if(x.length != y.length)
                        return null;

                int[] resultante = new int[x.length];
                for(int i = 0; i < x.length; i++)
                        resultante[i] = x[i] + y[i];

                return resultante;
        }

        public static double[] somar(double[] x, double[] y) {
                if(x.length != y.length)
                        return null;

                double[] resultante = new double[x.length];
                for(int i = 0; i < x.length; i++)
                        resultante[i] = x[i] + y[i];

                return resultante;
        }

        public static void imprimir(int[] vetor) {
                for(int i = 0; i < vetor.length; i++)
                        System.out.print(vetor[i] + " ");

                System.out.println();
        }

        public static void imprimir(double[] vetor) {
                for(int i = 0; i < vetor.length; i++)
                        System.out.print(vetor[i] + " ");

                System.out.println();
        }
}

public class Matriz {
        public static int[][] somar(int[][] x, int[][] y) {
                int[][] resultante = new int[x.length][x[0].length];

                for(int i = 0, j; i < x.length; i++) {
                        for(j = 0; j < x[0].length; j++)
                                resultante[i][j] = x[i][j] + y[i][j];
                }

                return resultante;
        }

        public static double[][] somar(double[][] x, double[][] y) {
                double[][] resultante = new double[x.length][x[0].length];

                for(int i = 0, j; i < x.length; i++) {
                        for(j = 0; j < x[0].length; j++)
                                resultante[i][j] = x[i][j] + y[i][j];
                }

                return resultante;
        }

        public static void imprimir(int[][] matriz) {
                for(int i = 0, j; i < matriz.length; i++) {
                        for(j = 0; j < matriz[0].length; j++)
                                System.out.print(matriz[i][j] + " ");
                        System.out.println();
                }
        }

        public static void imprimir(double[][] matriz) {
                for(int i = 0, j; i < matriz.length; i++) {
                        for(j = 0; j < matriz[0].length; j++)
                                System.out.print(matriz[i][j] + " ");
                        System.out.println();
                }
        }
}

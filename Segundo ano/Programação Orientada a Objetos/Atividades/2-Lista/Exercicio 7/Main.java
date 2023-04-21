public class Main {
        public static void main(String[] args) {
                int[][] matriz1 = {{1,2,3}, {1,2,3}, {1,2,3}};
                int[][] matriz2 = {{4,5,6}, {4,5,6}, {4,5,6}};
                int[][] matrizSoma = Matriz.somar(matriz1, matriz2);
                Matriz.imprimir(matrizSoma);
        }
}

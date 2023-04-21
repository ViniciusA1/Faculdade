public class Main {
        public static void main(String[] args) {
                Livro livro1 = new Livro("teste", "Teste", 2023, 0, 32.5);
                Capitulo capitulo = new Capitulo("Teste", 10, "Autor");

                livro1.imprimirDados();
                livro1.adicionaCapitulo(capitulo);
                System.out.println();
                livro1.imprimirDados();
        }
}

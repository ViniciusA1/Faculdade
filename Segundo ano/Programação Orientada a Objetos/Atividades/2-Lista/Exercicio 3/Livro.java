import java.util.List;
import java.util.ArrayList;

public class Livro {
        private String editor;
        private String titulo;
        private int ano;
        private int edicao;
        private double preco;
        List<Capitulo> capitulos;

        public Livro(String editor, String titulo, int ano, int edicao, double preco) {
                this.editor = editor;
                this.titulo = titulo;
                this.ano = ano;
                this.edicao = edicao;
                this.preco = preco;
                capitulos = new ArrayList<>();
        }

        public void adicionaCapitulo(Capitulo capitulo) {
                capitulos.add(capitulo);
        }

        public void imprimirDados() {
                System.out.printf("Editora: %s\n" + 
                                  "Titulo: %s\n" + 
                                  "Ano: %d\n" +
                                  "Edição: %d\n" +
                                  "Preço: %.2f\n",
                                  editor, titulo, ano,
                                  edicao, preco);

                for(Capitulo capituloAux : capitulos) {
                        int ID = 0;
                        System.out.printf("==Capítulo %d==\n" +
                                           "Título: %s\n" +
                                           "Número de páginas: %d\n" +
                                           "Autor: %s\n",
                                           ID, capituloAux.getTitulo(), 
                                           capituloAux.getNumPaginas(), 
                                           capituloAux.getAutor());
                        ID++;
                }
        }
}

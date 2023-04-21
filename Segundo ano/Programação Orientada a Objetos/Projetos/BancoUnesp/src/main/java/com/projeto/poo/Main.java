package com.projeto.poo;

/**
 * Projeto de um "Banco Unesp"
 * Programa feito inteiramente com interfaces, terminal usado apenas para debuggar
 * Tratamentos de possíveis erros de entrada foram feitos em cada operação
 */

/**
 * Classe principal que inicializa o programa
 * @author Vinicius Augusto Toreli Borgue
 */
class Main {
    private static final String PATH = "src/main/java/com/projeto/poo/dadosBanco/";
    
    
    /**
     * Método principal onde o programa começa
     * @param args Argumentos oriundos da execução
     */
    @SuppressWarnings("empty-statement")
    public static void main(String[] args) {
        String arquivoBanco = PATH + "banco.txt";
        String arquivoAgencias = PATH + "agencias.txt";
        String arquivoContas = PATH + "contas.txt";
        
        DisplayBanco display = new DisplayBanco(arquivoBanco,
                                                arquivoAgencias, arquivoContas);
       
        while(display.login(arquivoContas));
    }
}

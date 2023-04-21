package com.projeto.poo;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import javax.swing.JOptionPane;
import java.util.Scanner;

/**
 * Classe que contém os dados do arquivo de extrato do usuário
 * @author Vinicius Augusto Toreli Borgue
 */
public class Extrato {
    private static final String PATH = "src/main/java/com/projeto/poo/extratos/";
    private final String nomeExtrato;
    
    /**
     * Método constrói o objeto da classe
     * @param CPF CPF que será usado para nomear o arquivo de extrato
     */
    public Extrato(String CPF) {
        nomeExtrato = CPF;
        verificaExistencia();
    }
    
    /**
     * Método verifica se arquivo existe e, se não, cria-o
     */
    private void verificaExistencia() {
        File arquivo = new File(PATH + nomeExtrato + ".txt");
        
        if(arquivo.exists())
            return;
        
        try {
            arquivo.createNewFile();
        } catch(IOException error) {
            System.out.println("Não foi possível criar o arquivo!");
        }
    }
    
    /**
     * Método adiciona nova operação no arquivo de extrato
     * @param nome Nome (tipo) da operação
     * @param valor Valor da transação
     * @param saldo Saldo após operação
     */
    public void adicionaOperacao(String nome, double valor, double saldo) {
        FileWriter arquivo;
        LocalDate dataOperacao = LocalDate.now();
        DateTimeFormatter formataData = DateTimeFormatter.ofPattern("dd/MM/yyyy");
        String dataFormatada = dataOperacao.format(formataData);
        
        try {
            arquivo = new FileWriter(PATH + nomeExtrato + ".txt", true);
            arquivo.write(dataFormatada + " | " + nome + valor + 
                          " | " + "Saldo resultante: " + saldo + "\n");
            arquivo.close();
        } catch(IOException error) {
            System.out.println("Não foi possível escrever no arquivo!");
        }
    }
    
    /**
     * Método imprime o extrato da conta logada
     */
    public void imprimeExtrato() {
        File arquivo = new File(PATH + nomeExtrato + ".txt");
        Scanner read;
        String linha = new String();
        
        try {
            read = new Scanner(arquivo);
            
            while(read.hasNextLine()) {
                linha += read.nextLine() + "\n";
            }
            
            JOptionPane.showMessageDialog(null, linha, 
                    "Extrato", JOptionPane.PLAIN_MESSAGE);
        } catch(FileNotFoundException error) {
            System.out.println("Arquivo não pode ser aberto!");
        }
    }
}
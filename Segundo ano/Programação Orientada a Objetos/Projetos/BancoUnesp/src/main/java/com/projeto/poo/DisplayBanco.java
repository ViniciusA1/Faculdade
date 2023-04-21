package com.projeto.poo;

import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import javax.swing.*;

/**
 * Classe que contém o sistema do banco utilizado para logar e mostrar informações
 * em tela ao usuário
 * @author Vinicius Augusto Toreli Borgue
 */
public final class DisplayBanco {

    private Banco meuBanco;

    /**
     * Método constrói os objetos do banco através dos arquivos
     * @param banco Contém o nome do arquivo de banco
     * @param agencias Contém o nome do arquivo de agências
     * @param contas Contém o nome do arquivo de contas
     */
    public DisplayBanco(String banco, String agencias, String contas) {
        leArquivo(banco, 0);
        leArquivo(agencias, 1);
        leArquivo(contas, 2);
    }

    /**
     * Método recebe o nome do arquivo e cria os objetos necessários
     * @param nomeArquivo Nome do arquivo que deseja ler
     * @param flag Tipo do arquivo: 0 para banco, 1 para agência e 2 para conta
     */
    private void leArquivo(String nomeArquivo, int flag) {
        File arquivo = new File(nomeArquivo);

        try {
            Scanner readArquivo = new Scanner(arquivo);

            while (readArquivo.hasNextLine()) {
                String linha = readArquivo.nextLine();
                String[] dados = linha.split("#");
                criaDados(dados, flag);
            }

        } catch (FileNotFoundException error) {
            System.out.println("Erro! Arquivo não foi aberto!");
            System.exit(1);
        }
    }
    
    /**
     * Método cria os dados de acordo com o tipo de arquivo enviado
     * @param data String que contém os dados do arquivo separados
     * @param flag Tipo de arquivo enviado
     */
    private void criaDados(String[] data, int flag) {
        switch (flag) {
            case 0 ->  meuBanco = new Banco(data[0],
                    Integer.parseInt(data[1]), data[2], data[3]);
                    
            case 1 ->  meuBanco.cadastrarAgencia(data[0],
                    Integer.parseInt(data[1]), data[2]);
                   
            case 2 ->  meuBanco.cadastrarConta(data[0], data[1], data[2], data[3], 
                      Double.parseDouble(data[4]), 
                  Integer.parseInt(data[5]), 
                    Integer.parseInt(data[6]), data[7]);
        }
    }

    /**
     * Método coleta os dados para login do usuário
     * @param arquivoContas Nome do arquivo de contas
     * @return Se o usuário cancelar, retorna para sair do programa
     */
    @SuppressWarnings("empty-statement")
    public boolean login(String arquivoContas) {
        int escolhaUsuario, numAgencia, numConta;
        String senha;
        JTextField agencia = new JTextField();
        JTextField conta = new JTextField();
        JPasswordField senhaTexto = new JPasswordField();

        Object[] entradaDados = {"Agência: ", agencia, "Número da conta: ",
            conta, "Senha: ", senhaTexto};

        escolhaUsuario = JOptionPane.showConfirmDialog(null,
                entradaDados, "Bem-Vindo ao Banco Unesp!",
                JOptionPane.OK_CANCEL_OPTION);
        
        if(verificaSaida(escolhaUsuario)) {
            salvaDados(arquivoContas);
            return false;
        }
        
        try {
            numAgencia = Integer.parseInt(agencia.getText());
            numConta = Integer.parseInt(conta.getText());
            senha = new String(senhaTexto.getPassword());
        } catch(NumberFormatException erro) {
            displayCampoErro("Campos incorretos!");
            return true;
        }

        if (!meuBanco.logarCliente(numAgencia, numConta, senha))
        {
            displayCampoErro("Não foi possível logar! Dados inválidos!");
            return true;
        }

        JOptionPane.showMessageDialog(null, "Usuário logado com sucesso!",
                "Login correto", JOptionPane.INFORMATION_MESSAGE);
        
        while (telaUsuario());
        return true;
    }

    /**
     * Método imprime tela principal do usuário
     * @return Retorna false se o usuário deseja sair
     */
    private boolean telaUsuario() {
        Object[] opcoes = {"Saldo", "Depósito", "Saque", 
                           "Transferência", "Pix", "Extrato", "Sair"};
        
        int userOpt = JOptionPane.showOptionDialog(null, 
                "Operações disponíveis", "Menu - Cliente", 
                JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE,
                null, opcoes, opcoes[0]);
        
        return verificaOpcao(userOpt);
    }

    /**
     * Método verifica opção escolhida pelo usuário
     * @param opcao Opção escolhida pelo usuário
     * @return Retorna false se a escolha foi a saída
     */
    private boolean verificaOpcao(int opcao) {
        switch (opcao) {
            case 0 ->   operacaoSaldo();
            case 1 ->   operacaoDeposito();
            case 2 ->   operacaoSaque();
            case 3 ->   operacaoTransferencia();
            case 4 ->   operacaoPix();
            case 5 ->   operacaoExtrato();
            case 6 -> { operacaoSair(); return false; }
        }

        return true;
    }

    /**
     * Método realiza a operação saldo no banco cadastrado
     */
    private void operacaoSaldo() {
        JOptionPane.showMessageDialog(null, "Saldo da conta: " + meuBanco.buscarSaldo(), 
                "Saldo", JOptionPane.PLAIN_MESSAGE);
    }

    /**
     * Método realiza a operação depósito no banco cadastrado
     */
    private void operacaoDeposito() {
        double valor;
        JTextField valorDeposito = new JTextField();
        Object[] campos = {"Digite o valor do depósito", valorDeposito};
        
        if(displayCampos(campos, "Depósito")) return;
        
        try {
            valor = Double.parseDouble(valorDeposito.getText());
        } catch(NumberFormatException error) {
            displayCampoErro("Campos incorretos!");
            return;
        }

        if(!meuBanco.realizarDeposito(valor)) 
            displayCampoErro("Não foi possível concluir o depósito! "
                    +        "Valor inválido!");
        else 
            displaySucesso("Depósito concluído!");
    }

    /**
     * Método realiza a operação saque no banco cadastrado
     */
    private void operacaoSaque() {
        double valor;
        JTextField valorSaque = new JTextField();
        Object[] campos = {"Digite o valor do saque", valorSaque};
        
        if(displayCampos(campos, "Saque")) return;
        
        try {
            valor = Double.parseDouble(valorSaque.getText());
        } catch(NumberFormatException error) {
            displayCampoErro("Campos incorretos!");
            return;
        }
       
        if(!meuBanco.realizarSaque(valor)) 
            displayCampoErro("Não foi possível concluir o saque! "
                    +        "Valor inválido!");
        else 
            displaySucesso("Saque concluído!");
    }

    /**
     * Método realiza a operação de transferência no banco cadastrado
     */
    private void operacaoTransferencia() {
        int numAgencia, numConta;
        double valor;
        JTextField destAgencia = new JTextField();
        JTextField destConta = new JTextField();
        JTextField destValor = new JTextField();
        Object[] campos = {"Agência do destinatário", destAgencia, 
                           "Conta do destinatário", destConta, 
                           "Valor da transferência", destValor};
        
        if(displayCampos(campos, "Transferência")) return;
        
        try {
            numAgencia = Integer.parseInt(destAgencia.getText());
            numConta = Integer.parseInt(destConta.getText());
            valor = Double.parseDouble(destValor.getText());
        } catch(NumberFormatException error) {
            displayCampoErro("Campos incorretos!"); return;
        }
        
        if(!meuBanco.realizarTransferencia(numConta, numAgencia, valor)) 
            displayCampoErro("Não foi possível concluir a transferência!");
        else 
            displaySucesso("Transferência concluída!");
    }

    /**
     * Método realiza a operação de Pix no banco cadastrado
     */
    private void operacaoPix() {
        double valor;
        String CPF;
        JTextField destCPF = new JTextField();
        JTextField destValor = new JTextField();
        Object[] campos = {"CPF do destinatário", destCPF, 
                           "Valor do Pix", destValor};
        
        if(displayCampos(campos, "Pix")) return;
        
        CPF = destCPF.getText();
        try {
            valor = Double.parseDouble(destValor.getText());
        } catch(NumberFormatException error) {
            displayCampoErro("Campos incorretos!"); 
            return;
        }
        
        if(!meuBanco.realizarPix(CPF, valor))
            displayCampoErro("Não foi possível concluir o Pix! "
                    +        "CPF ou valor inválido");
        else
            displaySucesso("Pix concluído!");
    }
    
    private void operacaoExtrato() {
        meuBanco.realizarExtrato();
    }

    /**
     * Método realiza a operação de sair no banco cadastrado
     */
    private void operacaoSair() {
        meuBanco.deslogarConta();
        JOptionPane.showMessageDialog(null, 
                "Conta deslogada! Obrigado por utilizar nossos serviços!");
    }
    
    /**
     * Método mostra os campos para preenchimento na tela
     * @param campos Objeto com os campos a serem mostrados
     * @param tipoOperacao String com o nome da operação a ser executada
     * @return Retorna false se o usuário cancelar a operação
     */
    private boolean displayCampos(Object[] campos, String tipoOperacao) {
        int output = JOptionPane.showConfirmDialog(null, 
                campos, tipoOperacao, JOptionPane.OK_CANCEL_OPTION);
        
        return verificaSaida(output);
    }
    
    /**
     * Método exibe mensagem de erro ao usuário
     * @param tipo Tipo do erro encontrado
     */
    private void displayCampoErro(String tipo) {
        JOptionPane.showMessageDialog(null, 
                tipo, "Erro", JOptionPane.ERROR_MESSAGE);
    }
    
    /**
     * Método exibe mensagem de sucesso ao usuário
     * @param message Mensagem que varia de acordo com a operação que foi concluída
     */
    private void displaySucesso(String message) {
        JOptionPane.showMessageDialog(null, message);
    }
    
    /**
     * Método verifica se o usuário deseja sair ou cancelar a operação
     * @param saida Saida proveniente da interface
     * @return Retorna true se usuário deseja sair da operação
     */
    private boolean verificaSaida(int saida) {
        if(saida == JOptionPane.CANCEL_OPTION || saida == JOptionPane.CLOSED_OPTION || 
           saida == JOptionPane.NO_OPTION) 
        {
            JOptionPane.showMessageDialog(null, "Operação cancelada!");
            return true;
        }
        
        return false;
    }
    
    /**
     * Método escreve todas as alterações de dados novamente no arquivo de contas.
     * @param nomeArquivo Nome do arquivo de contas
     */
    private void salvaDados(String nomeArquivo) {
        FileWriter escritor;
        
        try {
            escritor = new FileWriter(nomeArquivo, false);
            meuBanco.salvaAgencias(escritor);
            escritor.close();  
        } catch(IOException erro) {
            System.out.println("Erro durante a escrita");
        }
    }
}
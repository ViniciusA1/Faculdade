package com.projeto.poo;

/**
 * Classe que contém as informações de cada conta do banco
 * @author Vinicius Augusto Toreli Borgue
 */
public class Conta {
    private final int numero;
    private double saldo;
    private final String nome;
    private final String endereco;
    private final String CPF;
    private final String dataNascimento;
    private String senha;
    private final Extrato extrato;
    private final double limiteSaldo;
    
    
    /**
     * Método constrói a conta
     * @param numero Número da conta
     * @param saldo Saldo da conta
     * @param nome Nome do usuário
     * @param endereco Endereço do usuário
     * @param CPF CPF do usuário
     * @param dataNascimento Data de nascimento do usuário
     * @param senha Senha do usuário
     */
    public Conta(int numero, double saldo, String nome, String endereco, 
                 String CPF, String dataNascimento, String senha) {
        this.numero = numero;
        this.saldo = saldo;
        this.nome = nome;
        this.endereco = endereco;
        this.CPF = CPF;
        this.dataNascimento = dataNascimento;
        this.senha = senha;
        this.limiteSaldo = 0;
        extrato = new Extrato(CPF);
    }
    
    /**
     * Método retorna o número da conta cadastrada
     * @return Retorna número da conta 
     */
    public int getNumero() {
        return numero;
    }

    /**
     * Método retorna o saldo presente na conta cadastrada
     * @return Retorna saldo da conta 
     */
    public double getSaldo() {
        return saldo;
    }

    /**
     * Método retorna o nome do dono da conta
     * @return Retorna nome do usuário
     */
    public String getNome() {
        return nome;
    }

    /**
     * Método retorna o endereço do dono da conta
     * @return Retorna endereço do usuário
     */
    public String getEndereco() {
        return endereco;
    }

    /**
     * Método retorna o CPF do dono da conta
     * @return Retorna CPF do usuário
     */
    public String getCPF() {
        return CPF;
    }

    /**
     * Método retorna a data de nascimento do dono da conta
     * @return Retorna data de nascimento do usuário
     */
    public String getDataNascimento() {
        return dataNascimento;
    }
    
    /**
     * Método seta uma nova senha para o usuário
     * @param novaSenha Nova senha digitada pelo usuário
     */
    public void setSenha(String novaSenha) {
        senha = novaSenha;
    }
    
    /**
     * Método deposita na conta um valor especificado
     * @param valor Valor a ser depositado
     * @return Retorna se o deposito foi ou não concluido com êxito
     */
    public boolean depositar(double valor) {
        if(valor > 0) {
            saldo += valor; 
            return true;
        }
        
        return false;
    }
    
    /**
     * Método saca da conta um valor especificado
     * @param valor Valor a ser sacado
     * @return Retorna se o saque foi ou não concluído com êxito
     */
    public boolean sacar(double valor) {
        if(valor <= 0 || saldo - valor < limiteSaldo) {
            System.out.println(valor);
            return false;
        }
            
        saldo -= valor;
        return true;
    }
    
    /**
     * Método mostra o extrato em tela
     */
    public void mostrarExtrato() {
        extrato.imprimeExtrato();
    }
    
    /**
     * Método salva operação realizada pelo cliente em seu extrato
     * @param tipo Tipo da operação realizada
     * @param valor Valor de transação
     */
    public void salvarOperacao(String tipo, double valor) {
        extrato.adicionaOperacao(tipo, valor, saldo);
    }
    
    /**
     * Método valida uma senha digitada pelo usuário na tela de login
     * @param senhaDigitada Senha digitada pelo usuário
     * @return Retorna se a senha está ou não correta
     */
    public boolean validarSenha(String senhaDigitada) {
        return (senha.compareTo(senhaDigitada) == 0);
    }
    
    /**
     * Método retorna os dados da conta em formato de string para ser colocado em arquivo
     * @param agencia Número da agência atual
     * @return Retorna os dados em forma de string
     */
    public String stringDados(int agencia) {
        return (nome + "#" + dataNascimento + "#" + endereco + "#" + CPF + "#" 
                + saldo + "#" + agencia + "#" + numero + "#" + senha + "\n");
    }
}
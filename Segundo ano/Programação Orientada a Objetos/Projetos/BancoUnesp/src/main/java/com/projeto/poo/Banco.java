package com.projeto.poo;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;
import javax.swing.JOptionPane;

/**
 * Classe que contém as informações do banco principal
 * @author Vinicius Augusto Toreli Borgue
 */
public class Banco {
    private final int numero;
    private final String nome;
    private final String CNPJ;
    private final String endereco;
    private Conta contaLogada;
    private int qtdAgencias;
    private List<Agencia> agencias;
    private HashMap<Integer, Integer> hashAgencia;
    
    /**
     * Método constrói o objeto da classe Banco
     * @param numero Número do banco
     * @param nome Nome do banco
     * @param CNPJ CNPJ do banco
     * @param endereco Endereço do banco
     */
    public Banco(String nome, int numero, String CNPJ, String endereco) {
        this.numero = numero;
        this.nome = nome;
        this.CNPJ = CNPJ;
        this.endereco = endereco;
        this.qtdAgencias = 0;
        agencias = new ArrayList<>();
        hashAgencia = new HashMap<>();
    }
    
    /**
     * Método loga o cliente e atribui a referência a contaLogada
     * @param numAgencia Número da agência escolhido
     * @param numConta Número da conta escolhido
     * @param senha Senha digitada
     * @return Retorna false se os dados estão incorretos ou true se o login foi
     * concluído
     */
    public boolean logarCliente(int numAgencia, int numConta, String senha) {
        Agencia agenciaAuxiliar = buscarAgencia(numAgencia);
        Conta contaAuxiliar;
        
        if(agenciaAuxiliar == null)
            return false;

        contaAuxiliar = agenciaAuxiliar.buscarConta(numConta);
        
        if(contaAuxiliar == null)
            return false;
        if(!contaAuxiliar.validarSenha(senha))
            return false;
        
        contaLogada = contaAuxiliar;
        return true;
    }
    
     /**
     * Método busca se agência existe e retorna-a
     * @param numeroAgencia Número da agência escolhido pelo usuário
     * @return Retorna nulo se o número é inválido, ou o elemento se o número é
     * válido
     */
    public Agencia buscarAgencia(int numeroAgencia) {
        Integer posi = hashAgencia.get(numeroAgencia);
        return (posi == null) ? null : agencias.get(posi);
    }
    
    /**
     * Método cadastra agência e guarda o número no mapa hash
     * @param agenciaFornecida Agencia fornecida pelo banco de dados
     */
    public void cadastrarAgencia(Agencia agenciaFornecida) {
        agencias.add(agenciaFornecida);
        hashAgencia.put(agenciaFornecida.getCodigo(), qtdAgencias);
        qtdAgencias++;
    }
    
    /**
     * Método cria nova agência com código escolhido
     * @param codigo Codigo da agência fornecida
     * @param nome Nome da agência fornecida
     * @param endereco Endereço da agência fornecida
     */
    public void cadastrarAgencia(String nome, int codigo, String endereco) {
        Agencia agenciaTemporaria = new Agencia(nome, codigo, endereco);
        cadastrarAgencia(agenciaTemporaria);
    }
    
    /**
     * Método cria nova conta na agência escolhida
     * @param numAgencia Número da agência fornecida
     * @param numConta Número da conta
     * @param nome Nome da conta
     * @param dataNascimento Data de nascimento do usuário
     * @param endereco Endereço do usuário
     * @param CPF CPF do usuário
     * @param saldo Saldo da conta do usuário
     * @param senha Senha do usuário
     */
    public void cadastrarConta(String nome, String dataNascimento, 
                               String endereco, String CPF, double saldo,
                               int numAgencia, int numConta, String senha)
    {
        Conta contaTemporaria = new Conta(numConta, saldo, nome, endereco, 
                                           CPF, dataNascimento, senha);
        
        agencias.get(numAgencia).cadastrarConta(contaTemporaria);
    }
    
    /**
     * Método realiza o saque na conta logada
     * @param valor Valor desejado pelo usuário
     * @return Retorna se o valor foi ou não sacado
     */
    public boolean realizarSaque(double valor) {
        if(contaLogada.sacar(valor)) {
            contaLogada.salvarOperacao("Saque: ", -valor);
            return true;
        }
        
        return false;
    }
    
    /**
     * Método realiza o depósito na conta logada
     * @param valor Valor desejado pelo usuário
     * @return Retorna se o valor foi ou não depositado
     */
    public boolean realizarDeposito(double valor) {
        if(contaLogada.depositar(valor)) {
            contaLogada.salvarOperacao("Depósito: ", valor);
            return true;
        }
        
        return false;
    }
    
    /**
     * Método retorna o saldo da conta logada
     * @return Retorna o valor numérico do saldo
     */
    public double buscarSaldo() {
        return contaLogada.getSaldo();
    }
    
    /**
     * Método transfere o valor da conta logada para outra
     * @param numConta Número da conta do destinatário
     * @param numAgencia Número da agência do destinatário
     * @param valor Valor que será transferido
     * @return Retorna se a transferência foi ou não concluída com êxito
     */
    public boolean realizarTransferencia(int numConta, int numAgencia, 
                                      double valor) 
    {
        Agencia agenciaReceptor = buscarAgencia(numAgencia);
        if(agenciaReceptor == null)
            return false;
        
        Conta contaReceptor = agenciaReceptor.buscarConta(numConta);
        if(contaReceptor == null)
            return false;
        
        return operacaoDupla(contaReceptor, agenciaReceptor, valor, "Transferência: ");
    }
    
    /**
     * Método transfere por Pix o valor desejado
     * @param chavePix Chave (CPF) do destinatário
     * @param valor Valor a ser utilizado
     * @return Retorna true se conseguiu realizar ou false se não
     */
    public boolean realizarPix(String chavePix, double valor) {
        Agencia agenciaReceptor = null;
        Conta contaReceptor = null;
        
        for(Agencia agenciaAux : agencias) {
            contaReceptor = agenciaAux.buscarCPF(chavePix);
            if(contaReceptor != null) {
                agenciaReceptor = agenciaAux;
                break;
            }
        }
        
        if(agenciaReceptor == null)
            return false;
        
        return operacaoDupla(contaReceptor, agenciaReceptor, valor, "Pix: ");
    }
    
    /**
     * Método busca o extrato da conta logada
     */
    public void realizarExtrato() {
        contaLogada.mostrarExtrato();
    }
    
    /**
     * Método desloga a conta atribuindo nulo à referência do objeto
     */
    public void deslogarConta() {
        contaLogada = null;
    }
    
    /**
     * Método imprime os dados do usuário que recebe uma operação
     * @param contaDesejada Referência para a conta que deseja imprimir
     * @param numAgencia Número da agência que deseja imprimir
     * @return Retorna a escolha do usuário (yes or no)
     */
    private int imprimeDados(Conta contaDesejada, int numAgencia, double valor) {
        int escolha;
        Object[] textos = {"Dados do destinatário\n\n", "Nome: " + 
                           contaDesejada.getNome(), "Agência: " + numAgencia, 
                           "Conta: " + contaDesejada.getNumero(), 
                           "\n\nSeu saldo: " + contaLogada.getSaldo(), 
                           "Valor a ser transferido: " + valor, 
                           "\nDeseja realmente continuar?"};
        
        escolha = JOptionPane.showConfirmDialog(null, textos,
                "Confirmação", JOptionPane.YES_NO_OPTION);
        
        return escolha;
    }
    
    /**
     * Método realiza dupla operação (saque e depósito) ao mesmo tempo
     * @param contaReceptor Conta do destinatário
     * @param agenciaReceptor Agência do destinatário
     * @param valor Valor a ser sacado/depositado
     * @return Retorna false se o usuário deseja cancelar a operação
     */
    private boolean operacaoDupla(Conta contaReceptor, Agencia agenciaReceptor, double valor, String tipo) {
        int saida = imprimeDados(contaReceptor,
                                 agenciaReceptor.getCodigo(), valor);
        
        if(saida == JOptionPane.NO_OPTION || saida == JOptionPane.CLOSED_OPTION)
            return false;
        
        if(contaLogada.sacar(valor)) {
            contaReceptor.depositar(valor);
            contaLogada.salvarOperacao(tipo, -valor);
            contaReceptor.salvarOperacao(tipo, valor);
            return true;
        }
        
        return false;
    }
    
    /**
     * Método salva alteração das contas de cada uma das agências
     * @param escritor Escritor que sobrescreve o arquivo
     * @throws IOException Usado para tratamento de erro
     */
    public void salvaAgencias(FileWriter escritor) throws IOException {
        for(Agencia agenciaAux : agencias)
            agenciaAux.salvarContas(escritor);
    }
}
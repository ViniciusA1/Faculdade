package com.projeto.poo;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;

/**
 * Classe que contém as informações e métodos de cada agência bancária
 * @author Vinicius Augusto Toreli Borgue
 */
public class Agencia {
    private final int codigo;
    private final String nome;
    private final String endereco;
    private int qtdContas;
    private List<Conta> account;
    private HashMap<Integer, Integer> hash;
    
    /**
     * Método constrói a agência
     * @param nome Nome da agência
     * @param codigo Código da agência
     * @param endereco Endereço da agência
     */
    public Agencia(String nome, int codigo, String endereco) {
        this.qtdContas = 0;
        this.codigo = codigo;
        this.nome = nome;
        this.endereco = endereco;
        account = new ArrayList<>();
        hash = new HashMap<>();
    }

    /**
     * Método retorn o código da agência cadastrada
     * @return Retorna o código da agência
     */
    public int getCodigo() {
        return codigo;
    }

    /**
     * Método retorna o nome da agência cadastrada
     * @return Retorna o nome da agência
     */
    public String getNome() {
        return nome;
    }

    /**
     * Método retorna o endereço da agência cadastrada
     * @return Retorna o endereço da agência
     */
    public String getEndereco() {
        return endereco;
    }
    
    /**
     * Método cadastra conta fornecida na agência
     * @param contaFornecida Conta fornecida pelo banco de dados
     */
    public void cadastrarConta(Conta contaFornecida) {
        account.add(contaFornecida);
        hash.put(contaFornecida.getNumero(), qtdContas);
        qtdContas++;
    }
    
    /**
     * Método retorna referência para conta com o devido número
     * @param numConta Número da conta digitado pelo usuário
     * @return Retorna a referência a conta
     */
    public Conta buscarConta(int numConta) {
        Integer posi = hash.get(numConta);
        return (posi == null) ? null : account.get(posi);
    }
    
    /**
     * Método retorna referência para a conta com o devido CPF
     * @param CPF CPF digitado pelo usuário
     * @return Retorna a referência a conta
     */
    public Conta buscarCPF(String CPF) {
        for(Conta contaAux : account) {
            if(contaAux.getCPF().compareTo(CPF) == 0)
                return contaAux;
        }
        
        return null;
    }
    
    /**
     * Método salva as contas modificadas no arquivo
     * @param escritor Escritor utilizado para sobrescrever o arquivo
     * @throws IOException Usado para tratamento de possíveis erros
     */
    public void salvarContas(FileWriter escritor) throws IOException  {
        for(Conta contaAux : account) {
            escritor.write(contaAux.stringDados(codigo));
        }
    }
}
import java.util.ArrayList;
import java.util.Scanner;

public class Core {
        private List<Cliente> cliente;
        private final Scanner read;


        public Core() {
                cliente = new ArrayList<>();
                read = new Scanner(System.in);
        }

        public void cadastrarCliente() {
                String nome, bairro, rua;
                int numCasa;

                System.out.print("Digite o nome: ");
                nome = read.nextLine();
                System.out.println("Digite o bairro: ");
                bairro = read.nextLine();
                System.out.println("Digite a rua: ");
                rua = read.nextLine();
                System.out.println("Digite o número da casa: ");
                numCasa = read.nextInt();
                
                Cliente clienteAux = new Cliente(nome, endereco);
                cliente.add(clienteAux);
        }

        public void removerCliente() {
                System.out.print("Digite o nome do cliente: ");
                String nome = read.nextLine();
                Cliente clienteAux = buscarCliente(nome);
                
                if(clienteAux != null)
                        cliente.remove(clienteAux);
        }

        public Cliente buscarCliente(String nome) {
                for(Cliente clienteTemp : cliente) {
                        if(nome.compareTo(clienteTemp.getNome()) == 0)
                                return clienteTemp;
                }

                return null;
        } 
}

public class Cliente {
        private String nome;
        private Endereco endereco;

        public Cliente(String nome, Endereco enderecoAux) {
                this.nome = nome;
                this.endereco = enderecoAux;
        }

        public String getNome() {
                return nome;
        }

        public Endereco getEndereco() {
                return endereco;
        }
}

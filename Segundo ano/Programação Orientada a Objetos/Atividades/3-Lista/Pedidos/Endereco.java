public class Endereco {
        private String bairro;
        private String rua;
        private int numeroCasa;

        public Endereco(String bairro, String rua, int numCasa) {
                this.bairro = bairro;
                this.rua = rua;
                this.numeroCasa = numCasa;
        }

        public String getBairro() {
                return bairro;
        }

        public String getRua() {
                return rua;
        }

        public int getNumeroCasa() {
                return numeroCasa;
        }
}

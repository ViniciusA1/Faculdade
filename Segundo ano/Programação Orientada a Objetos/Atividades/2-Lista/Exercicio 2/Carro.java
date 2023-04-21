public class Carro {
        private String placa;
        private String modelo;
        private Tempo dataInicio;
        private Tempo dataFim;
        private double preco;

        public Carro() {
                dataInicio = new Tempo();
                dataFim = new Tempo();
                placa = null;
                modelo = null;
                preco = 0;
        }

        public Carro(String placa, String modelo, int inicioH, 
                     int inicioM, int inicioS, int fimH, int fimM, int fimS) {
                this.placa = placa;
                this.modelo = modelo;
                dataInicio = new Tempo(inicioH, inicioM, inicioS);
                dataFim = new Tempo(fimH, fimM, fimS);
                preco = 1.5;
        }

        public String getPlaca() {
                return placa;
        }

        public String getModelo() {
                return modelo;
        }

        public Tempo getInicio() {
                return dataInicio;
        }

        public Tempo getFim() {
                return dataFim;
        }

        public double getPreco() {
                Tempo tempoAux = new Tempo();
                tempoAux.subtrair(dataFim, dataInicio);
                return tempoAux.getHoras() * preco;
        }

        public void imprimirDados() {
                System.out.printf("Placa: %s\n" +
                                  "Modelo: %s\n" + 
                                  "Data de início: %s\n" +
                                  "Data de fim: %s\n" +
                                  "Preço: %f\n",
                                  placa, modelo, 
                                  dataInicio.imprimirDados(), 
                                  dataFim.imprimirDados(), 
                                  getPreco());
        }
}

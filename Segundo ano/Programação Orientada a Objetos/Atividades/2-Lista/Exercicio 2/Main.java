public class Main {
        public static void main(String[] args) {
                Estacionamento estacionamento = new Estacionamento();
                Carro carro1 = new Carro("Placa", "Modelo", 10, 30, 20, 18, 23, 40);

                estacionamento.estacionarCarro(carro1);
                estacionamento.setarCarro(0);
                estacionamento.mostrarCarro();
        }
}

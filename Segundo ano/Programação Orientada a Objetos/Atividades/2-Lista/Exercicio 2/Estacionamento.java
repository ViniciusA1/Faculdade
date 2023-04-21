import java.util.List;
import java.util.ArrayList;

public class Estacionamento {
        private List<Carro> carros;
        private Carro carroAtual;

        public Estacionamento() {
                carros = new ArrayList<>();
                carroAtual = null;
        }

        public void estacionarCarro(Carro novoCarro) {
                carros.add(novoCarro);
        }

        public void retirarCarro(Carro carroDesejado) {
                carros.remove(carroDesejado);
        }

        public void setarCarro(int ID) {
                carroAtual = carros.get(ID);
        }

        public void mostrarCarro() {
                carroAtual.imprimirDados();
        }
}

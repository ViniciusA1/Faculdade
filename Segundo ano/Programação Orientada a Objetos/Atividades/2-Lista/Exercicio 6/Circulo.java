public class Circulo {
        public static double calcularArea(double raio) {
                return Math.PI * raio * raio;
        }

        public static double calcularArea(double diametro, boolean flag) {
                diametro = diametro / 2;
                return Math.PI * diametro * diametro;
        }
}

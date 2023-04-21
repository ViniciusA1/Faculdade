public class Tempo {
        private int horas; 
        private int minutos; 
        private int segundos;

        public Tempo() {
                horas = 0;
                minutos = 0;
                segundos = 0;
        }

        public Tempo(int horas, int minutos, int segundos) {
                this.horas = horas;
                this.minutos = minutos;
                this.segundos = segundos;
        }

        public int getHoras() {
                return horas;
        }

        public int getMinutos() {
                return minutos;
        }

        public int getSegundos() {
                return segundos;
        }

        public void setHoras(int horas) {
                this.horas = horas;
        }

        public void setMinutos(int minutos) {
                this.minutos = minutos;
        }

        public void setSegundos(int segundos) {
                this.segundos = segundos;
        }

        public String imprimirDados() {
                return (horas + ":" + minutos + ":" + segundos);
        }

        public void subtrair(Tempo tempo) {
                segundos -= tempo.getSegundos();
                minutos -= tempo.getMinutos();
                horas -= tempo.getHoras();
                formatar();
        }

        public void subtrair(Tempo tempo1, Tempo tempo2) {
                segundos = tempo1.getSegundos() - tempo2.getSegundos();
                minutos = tempo1.getMinutos() - tempo2.getMinutos();
                horas = tempo1.getHoras() - tempo2.getHoras();
                formatar();
        }

        public void somar(Tempo tempo) {
                segundos += tempo.getSegundos();
                minutos += tempo.getMinutos();
                horas += tempo.getHoras();
                formatar();
        }

        private void formatar() {
                if(segundos >= 60) {
                        minutos += segundos / 60;
                        segundos %= 60;
                } else if(segundos < 0) {
                        minutos--;
                        segundos += 60;
                }
                
                if(minutos >= 60) {
                        horas += minutos / 60;
                        minutos %= 60;
                } else if(minutos < 0) {
                        horas--;
                        minutos += 60;
                }

                if(horas >= 24)
                        horas %= 24;
                else if(horas < 0)
                        horas += 24;
        }
}

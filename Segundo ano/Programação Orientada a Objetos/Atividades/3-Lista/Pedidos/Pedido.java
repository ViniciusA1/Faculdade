public class Pedido {
        Cliente comprador;
        List<ItemPedido> item;

        public Pedido(Cliente comprador) {
                this.comprador = comprador;
                item = new ArrayList<>();
        }
}

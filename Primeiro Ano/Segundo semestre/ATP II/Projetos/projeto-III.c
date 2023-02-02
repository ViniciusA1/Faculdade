#include <stdio.h>
#include <stdlib.h>

/* Estrutura de cada elemento da lista:
 * I-> identificação;
 * K-> local da próxima remoção;
 * O-> variável de controle,
 * *prox-> apontamento para o próximo elemento.
 */

typedef struct circular
{
        int I, K, O;
        struct circular *prox;
} circ_t;

//=================|Protótipos|=================//

void create_elem(int, circ_t **, circ_t **);
void verify_list(circ_t *, circ_t *);

//=================|Principal|=================//

int main()
{
        circ_t *head = NULL;
        circ_t *tail = head;
        int N, i;

        scanf("%d", &N);
        // Cria os elementos de 1 a N.
        for (i = 0; i < N; i++)
                create_elem(i + 1, &head, &tail);

        verify_list(head, tail);

        return 0;
}

/* Função recebe id do número e ponteiros de cabeça e cauda.
 * Cria a estrutura do novo elemento e o insere na lista.*/
void create_elem(int num_alloc, circ_t **h, circ_t **t)
{
        circ_t *new_elem = malloc(sizeof(circ_t));

        new_elem->I = num_alloc;
        scanf("%d %d", &new_elem->K, &new_elem->O);

        if (!(*h)) // Lista vazia.
                *h = new_elem;
        else
                (*t)->prox = new_elem;

        // Caso geral.
        *t = new_elem;
        new_elem->prox = *h;
}

/* Função recebe ponteiros de cabeça e cauda.
 * Roda a lista e executa a função principal do algoritmo.*/
void verify_list(circ_t *h, circ_t *t)
{
        circ_t *temp = h, *ant = h, *store_aux = NULL, *ant_aux = NULL;
        int i, k_value = temp->K;

        // Percorre a lista até que reste apenas um elemento.
        while (temp != temp->prox)
        {
                for (i = 1; i < k_value; i++)
                {
                        ant = temp;
                        temp = temp->prox;
                }

                if (temp->O && store_aux)
                { // Reinsere se temp->O igual a um.
                        // Se o anterior do atual for igual ao anterior do removido, precisa-se atualizar a variável para futura remoção.
                        if (ant == ant_aux)
                                ant = store_aux;
                        store_aux->O = 0;
                        store_aux->prox = ant_aux->prox;
                        ant_aux->prox = store_aux;
                }
                else if (store_aux) // Em todo caso, libera o removido.
                        free(store_aux);

                store_aux = temp; // Guarda o elemento que será retirado.
                ant_aux = ant;    // Guarda o anterior para possível reinserção.
                ant->prox = temp->prox;
                k_value = temp->K; // Pega o valor de K para remover o próximo.
                temp = temp->prox;
        }

        printf("%d\n", temp->I);
        free(temp);      // Limpa o último elemento na lista.
        free(store_aux); //  Limpa o último elemento guardado.
}
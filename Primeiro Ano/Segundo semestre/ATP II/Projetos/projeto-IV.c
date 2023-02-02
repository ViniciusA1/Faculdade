#include <stdio.h>
#include <stdlib.h>

/* Atributos de cada elemento da fila:
 * -> ID: identificador de elemento;
 * -> Arrive: tempo de chegada de um elemento;
 * -> Cost: tempo que o elemento permanece na fila,
 * -> *Prox: ponteiro para o próximo elemento.
 */

typedef struct Fila
{
        int id, arrive, cost;
        struct Fila *prox;
} fila;

// ================|Protótipos|================ //

void add_node(fila **);
void process_list(fila *, int);
int lowest_time(int[], int);

// ================|Principal|================ //

int main()
{
        fila *head = NULL;
        int M, N, i;

        scanf("%d %d", &M, &N);
        // Cria todos os elementos na fila.
        for (i = 0; i < M; i++)
                add_node(&head);

        // Atende todos os elementos na fila.
        process_list(head, N);
        return 0;
}

/* Função recebe o ponteiro do elemento da cabeça.
 * Adiciona os elementos lidos de acordo com a ordem de prioridade na fila. */
void add_node(fila **h)
{
        fila *aux = *h, *ant = *h;
        fila *new = malloc(sizeof(fila));
        new->prox = NULL;

        scanf("%d %d %d", &new->id, &new->arrive, &new->cost);

        // Fila vazia.
        if (!(*h))
        {
                *h = new;
                return;
        }

        // Continua a andar se o tempo de chegada for maior, ou se for igual e o id for maior.
        while (aux && ((new->arrive > aux->arrive) || (new->arrive == aux->arrive &&new->id > aux->id)))
        {
                ant = aux;
                aux = aux->prox;
        }

        // Inserção antes da cabeça.
        if (aux == *h)
        {
                new->prox = *h;
                *h = new;
                return;
        }

        new->prox = ant->prox;
        ant->prox = new;
}

/* Função recebe o ponteiro do elemento cabeça e número de atendentes.
 * Para cada processo na fila, move-o para o seu respectivo atendente, aumentando seu tempo total. */
void process_list(fila *start, int workers)
{
        fila *temp; // Auxiliar usado para liberar memória.
        int process_line[workers], id;

        // Começa com zero.
        for (id = 0; id < workers; id++)
                process_line[id] = 0;

        while (start)
        {
                // Procura o atendente com menor tempo total.
                id = lowest_time(process_line, workers);
                // Se o tempo do atendente for menor, recebe o tempo atual e sua duração.
                if (process_line[id] < start->arrive)
                        process_line[id] = start->arrive + start->cost;
                else
                        process_line[id] += start->cost;
                temp = start;
                start = start->prox;
                free(temp);
        }

        // Printa o vetor com todos os tempos acumulados dos N atendentes.
        for (id = 0; id < workers; id++)
                printf("%d ", process_line[id]);
        printf("\n");
}

/* Função recebe o vetor de atendentes e a sua quantidade.
 * Retorna o índice do atendente com o menor tempo acumulado. */
int lowest_time(int search[], int stop)
{
        int i, current_id = 0;

        for (i = 0; i < stop; i++)
        {
                if (search[current_id] > search[i])
                        current_id = i;
        }

        return current_id;
}
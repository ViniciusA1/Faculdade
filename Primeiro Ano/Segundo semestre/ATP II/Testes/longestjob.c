#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int tempo, carga;
    struct process *prox;
} proc_t;

void add_elem(proc_t **h)
{
    proc_t *aux, *ant;
    proc_t *new = malloc(sizeof(proc_t));
    aux = ant = *h;
    new->prox = NULL;

    scanf("%d %d", &new->tempo, &new->carga);

    if(!(*h)) {
        *h = new;
        return;
    }

    while(aux && new->tempo > aux->tempo) {
        ant = aux;
        aux = aux->prox;
    }

    if(aux == *h && new->tempo < aux->tempo) {
        new->prox = *h;
        *h = new;
        return;
    }

    new->prox = ant->prox;
    ant->prox = new;
}

void print_list(proc_t *h)
{
    proc_t *aux;
    
    while(h) {
        aux = h;
        printf("%d ", aux->carga);
        h = h->prox;
        free(aux);
    }

    printf("\n");
}

int main()
{
    proc_t *head = NULL;
    proc_t *aux, *temp, *ant;
    proc_t *ant_maior, *temp_maior;
    int N, sum, i;

    scanf("%d", &N);

    for(i = 0; i < N; i++)
        add_elem(&head);

    aux = head;
    sum = aux->tempo;
    
    while(aux->prox) {
        if(aux->tempo <= sum)
            sum += aux->carga;
        else
            sum = aux->tempo + aux->carga;
        
        temp = ant = aux->prox;
        temp_maior = ant_maior = aux->prox;

        while(temp && temp->tempo <= sum) {
            if(temp->carga > temp_maior->carga) {
                ant_maior = ant;
                temp_maior = temp;
            }
            ant = temp;
            temp = temp->prox;
        }
        
        if(aux->prox != temp_maior) {
            ant_maior->prox = temp_maior->prox;
            temp_maior->prox = aux->prox;
            aux->prox = temp_maior;
        }
        aux = aux->prox;
    }

    print_list(head);
    return 0;
}

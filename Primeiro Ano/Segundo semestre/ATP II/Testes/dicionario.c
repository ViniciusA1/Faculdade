#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct palavra {
    char nome[50];
    struct palavra *prox;
} lista_t;

void add_palavra(lista_t **h)
{
    int temp;
    lista_t *new = malloc(sizeof(lista_t));
    lista_t *antes = *h, *aux = *h;

    scanf("%s", new->nome);
    new->prox = NULL;

    if(!(*h)) {
        (*h) = new;
        return;
    }

    while(aux && strcmp(aux->nome, new->nome) < 0) {
        antes = aux;
        aux = aux->prox;
    }

    if(aux && !strcmp(aux->nome, new->nome)) {
        free(new);
        return;
    }

    if(aux == (*h)) {
        new->prox = (*h);
        (*h) = new;
    }
    else {
        new->prox = aux;
        antes->prox = new;
    }
}

void remove_palavra(lista_t **h)
{
    lista_t *aux, *antes;
    char elem[50];
    aux = antes = (*h);

    scanf("%s", elem);
    if(!(*h))
        return;

    while(aux->prox && strcmp(elem, aux->nome) != 0) {
        antes = aux;
        aux = aux->prox;
    }

    if(!strcmp(elem, aux->nome)) {
        if(aux == (*h))
            (*h) = aux->prox;
        else
            antes->prox = aux->prox;

        free(aux);
    }
}

void limpa_mem(lista_t *h)
{
    lista_t *aux;

    while(h) {
        aux = h;
        h = h->prox;
        free(aux);
    }
}

void imprime_lista(lista_t *start)
{
    if(!start) {
        printf("NULL\n");
        return;
    }

    while(start) {
        printf("%s ", start->nome);
        start = start->prox;
    }

    printf("\n");
}

int main()
{
    lista_t *head = NULL, *aux;
    int N, M, i, op;
    char word[100];
    
    scanf("%d %d", &N, &M);

    for(i = 0; i < N; i++)
        add_palavra(&head);

    for(i = 0; i < M; i++) {
        scanf("%d", &op);
        if(op == 0)
            remove_palavra(&head);
        else if(op == 1)
            add_palavra(&head);
        else if(op == 2) {
            aux = head;
            scanf("%s", word);
            while(aux && strcmp(word, aux->nome) > 0)
                aux = aux->prox;
            imprime_lista(aux);
        }
    }

    limpa_mem(head);

    return 0;
}

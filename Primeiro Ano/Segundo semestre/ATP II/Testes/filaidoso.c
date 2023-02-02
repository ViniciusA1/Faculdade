#include <stdio.h>
#include <stdlib.h>

typedef struct Fila {
        int age, arrive;
        struct Fila *next;
} queue;

void add_auxiliar_queue(queue **start)
{
        queue *new = malloc(sizeof(queue));
        queue *current = *start, *prev = *start;

        scanf("%d %d", &new->age, &new->arrive);

        if(!(*start)) {
                *start = new;
                return;
        }

        while(current && (new->arrive > current->arrive || (new->arrive == current->arrive && new->age <= 59))) {
                prev = current;
                current = current->next; 
        }

        if(current == *start) {
                new->next = prev;
                *start = new;
                return;
        }

        new->next = prev->next;
        prev->next = new;
}

void print_queue(queue *beginning)
{
        while(beginning) {
                printf("%d ", beginning->age);
                beginning = beginning->next;
        }

        printf("\n");
}

void add_main_queue(queue **begin_aux, queue **begin_main, queue **end_main)
{
        queue *now = *begin_main, *prev = *begin_main, *temp = *begin_aux;
        (*begin_aux) = (*begin_aux)->next;

        if(!(*begin_main)) {
                *begin_main = *end_main = temp;
                temp->next = NULL;
                return;
        }

        if(temp->age > 59) {
                prev = now;
                now = now->next;
                while(now && temp->age < now->age) {
                        prev = now;
                        now = now->next;
                }
                
                if(now == NULL)
                        *end_main = temp;

                temp->next = prev->next;
                prev->next = temp;
        }
        else {
                (*end_main)->next = temp;
                temp->next = NULL;
                (*end_main) = temp;
        }
}

void remove_head(queue **head, int *total_time, int current_time, queue *temp_head)
{
        queue *free_ptr;

        while((*head) && current_time >= *total_time) {
                free_ptr = *head;
                (*head) = (*head)->next;
                free(free_ptr);
                if((*head) != NULL) {
                        if((*head)->arrive < *total_time)
                                *total_time += 3;
                        else
                                *total_time = (*head)->arrive + 3;
                }
                else {
                        if(temp_head->arrive < *total_time)
                                *total_time += 3;
                        else
                                *total_time = temp_head->arrive + 3;
                }
        }
}

void clear_memory(queue *clear_target)
{
        queue *free_ptr;

        while(clear_target) {
                free_ptr = clear_target;
                clear_target = clear_target->next;
                free(free_ptr);
        }
}

int main()
{
        queue *auxiliar_head = NULL;
        queue *main_head = NULL, *main_tail = NULL;
        int number_of_persons, i, current_arrive, sum = 0;

        scanf("%d", &number_of_persons);

        for(i = 0; i < number_of_persons; i++)
                add_auxiliar_queue(&auxiliar_head);

        sum = auxiliar_head->arrive + 3;
        while(auxiliar_head) {
                current_arrive = auxiliar_head->arrive;
                
                while(auxiliar_head && auxiliar_head->arrive == current_arrive) {
                        remove_head(&main_head, &sum, current_arrive, auxiliar_head);
                        add_main_queue(&auxiliar_head, &main_head, &main_tail);
                }

                print_queue(main_head);
        }

        clear_memory(main_head);
        clear_memory(auxiliar_head);

        return 0;
}

#include "include/main.h"

void createSet(Set **A) 
{
        *A = calloc(sizeof(Set), 1);
}

Element *findMiddle(Element *begin, Element *end)
{
        Element *back = begin, *front = begin->next;

        while(front != end) {
                front = front->next;
                if(front != end) {
                        front = front->next;
                        back = back->next;
                }
        }

        return back;
}

bool memberOfSet(double elem, Set *A)
{
        if(!A->head)
                return false;

        if(A->head->value == elem)
                return true;

        Element *begin = A->head;
        Element *last = NULL;
        Element *middle;

        for(;!last || last != begin;) {
                middle = findMiddle(begin, last);

                if(middle->value == elem)
                        return true;
                else
                        (elem > middle->value) ? 
                        (begin = middle->next) : (last = middle);
        }

        return false;
}

Element *insertElement(double elem, Set *set)
{
        if(memberOfSet(elem, set)) {
                puts("This element is already on the set");
                return set->head;
        }

        Element *tmp = set->head;
        Element *new = calloc(sizeof(Element), 1);
        new->value = elem;

        if(!set->head) 
                return new;
        if(tmp->value > elem) {
                new->next = tmp;
                return new;
        }

        while(!tmp->next && tmp->next->value < elem)
                tmp = tmp->next;

        new->next = tmp->next;
        tmp->next = new;

        return set->head;
}

bool checkEqual(Set *A, Set *B)
{
        if(A->elem_amount != B->elem_amount)
                return false;

        Element *aux_A = A->head, *aux_B = B->head;

        while(!aux_A) {
                if(aux_A->value != aux_B->value)
                        return false;
                
                aux_A = aux_A->next;
                aux_B = aux_B->next;
        }

        return true;
}

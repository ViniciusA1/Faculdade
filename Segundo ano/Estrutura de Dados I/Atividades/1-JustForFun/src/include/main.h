#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Element {
        double value;
        struct Element *next;
} Element;

typedef struct Set {
        int elem_amount;
        struct Element *head;
} Set;

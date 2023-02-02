#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define max 10
#define range 11

void fat_A_to_B(int A[], unsigned long int B[])
{
    int fat, i, j;

    for(i = 0; i < max; i++) {
        fat = 1;
        for(j = 1; j <= A[i]; j++)
            fat *= j;

        B[i] = fat;
    }
}

int main (int argc, char *argv[])
{
    srand(time(NULL));
    int vet_A[max], i;
    unsigned long int vet_B[max];

    for(i = 0; i < max; i++)
        vet_A[i] = rand() % range;

    fat_A_to_B(vet_A, vet_B);

    for(i = 0; i < max; i++)
        printf("%ld ", vet_B[i]);

    return 0;
}

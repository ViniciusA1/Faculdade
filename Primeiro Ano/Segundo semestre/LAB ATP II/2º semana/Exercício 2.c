#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define range 101
#define n 10
#define m 5

int quant_divisores(int num, int vet_temp[])
{
    int i, count = 0;

    for(i = 0; i < m; i++) {
        if(!(num % vet_temp[i]))
            count++;
    }

    return count;
}

int main()
{
    srand(time(NULL));
    int vet[n], vet_2[m], i, soma_par = 0, vet_res[m], vet_res_2[n] = {0};

    for(i = 0; i < n; i++) {
        vet[i] = rand() % range;
        if(!(vet[i] % 2))
            soma_par += vet[i];
    }

    for(i = 0; i < m; i++) {
        vet_2[i] = rand() % range;
        vet_res[i] = soma_par + vet_2[i];
    }

    for(i = 0; i < n; i++) {
        if(vet[i] % 2) {
            vet_res_2[i] = quant_divisores(vet[i], vet_2);
        }
    }

    return 0;
}
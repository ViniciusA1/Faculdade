#include <stdio.h>
#define max 200000
#define condition !(bigint[i].high > bigint[pivo].high || \
                    (bigint[i].high == bigint[pivo].high && (bigint[i].high >= 0 ? bigint[i].low > bigint[pivo].low : bigint[i].low < bigint[pivo].low)))

// Struct que contém os componentes do dado "BigInt"
// high: Corresponde a casa dos bilhões,
// low: Valores menores que um bilhão.

typedef struct bigint
{
        int high, low;
} bigint_t;

//========|Protótipos|========//

void quicksort(bigint_t *, int, int);
void change_value(bigint_t *, bigint_t *);

//========|Principal|=========//

int main()
{
        int i;
        FILE *file_pointer = fopen("bigint.dat", "r");
        bigint_t bigint[max];

        // Lê a struct da forma como aparece no arquivo.
        for (i = 0; i < max; i++)
                fscanf(file_pointer, "%d %d", &bigint[i].high, &bigint[i].low);

        // Fecha arquivo para abrir o próximo.
        fclose(file_pointer);

        // Realiza a ordenação da struct.
        quicksort(bigint, 0, max - 1);

        // Abre arquivo de output.
        file_pointer = fopen("quick.dat", "w");

        // Escreve a struct ordeanda no arquivo de output.
        for (i = 0; i < max; i++)
                fprintf(file_pointer, "%d %d\n", bigint[i].high, bigint[i].low);

        fclose(file_pointer);
        return 0;
}

// Função recebe struct, menor e maior índice.
// Ordena a struct desejada, utilizando o algoritmo quicksort.
void quicksort(bigint_t *bigint, int begin, int end)
{
        int i, pivo = end, changer = begin;

        if (begin >= end)
                return;

        for (i = begin; i < end; i++)
        {
                if (condition)
                {
                        change_value(&bigint[i], &bigint[changer]);
                        changer++;
                }
        }

        change_value(&bigint[pivo], &bigint[changer]);
        quicksort(bigint, begin, changer - 1);
        quicksort(bigint, changer + 1, end);
}

void inline change_value(bigint_t *target_1, bigint_t *target_2)
{
        bigint_t store_aux = *target_1;
        *target_1 = *target_2;
        *target_2 = store_aux;
}
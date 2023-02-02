#include <stdio.h>
#define max 200000
#define condition j >= 0 && (bigint[j].high > aux.high ||   \
                             (bigint[j].high == aux.high && \
                              (bigint[j].high >= 0 ? bigint[j].low > aux.low : bigint[j].low < aux.low)))

// Struct que contém os dados para o tipo "BigInt"
// high: Corresponde a casa dos bilhões,
// low: Valores menores que um bilhão.

typedef struct biggo
{
        int high, low;
} bigint_t;

//========|Protótipos|========//

void insertion_sort(bigint_t *);

//========|Principal|=========//

int main()
{
        FILE *fp = fopen("bigint.dat", "r");
        int i;
        bigint_t bigint[max];

        // Lê os dados do arquivo na ordem que foram apresentados.
        for (i = 0; i < max; i++)
                fscanf(fp, "%d %d", &bigint[i].high, &bigint[i].low);

        fclose(fp);
        fp = fopen("insertion.dat", "w");

        // Ordena os dados da struct de forma crescente.
        insertion_sort(bigint);

        // Guarda a struct ordenada no arquivo.
        for (i = 0; i < max; i++)
                fprintf(fp, "%d %d\n", bigint[i].high, bigint[i].low);

        fclose(fp);
        return 0;
}

// Função recebe vetor de structs.
// Ordena os dados utilizando o algortimo insertion sort.
void insertion_sort(bigint_t bigint[max])
{
        bigint_t aux;
        int i, j;

        for (i = 1; i < max; i++)
        {
                aux = bigint[i];

                for (j = i - 1; condition; j--)
                        bigint[j + 1] = bigint[j];

                bigint[j + 1] = aux;
        }
}
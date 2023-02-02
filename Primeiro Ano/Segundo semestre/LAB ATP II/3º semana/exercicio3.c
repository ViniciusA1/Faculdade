#include <stdio.h>
#include <stdlib.h>

typedef struct habitante {
    float sal;
    int num_filhos;
} habi_t;

void le_dados(int max, habi_t h[max], float result[])
{
    int i;

    for(i = 0; i < max; i++) {
        scanf("%f", &h[i].sal);
        scanf("%d", &h[i].num_filhos);
        result[0] += h[i].sal;
        result[1] += h[i].num_filhos;

        if(h[i].sal > result[2])
            result[2] = h[i].sal;

        if(h[i].sal < 1000)
            result[3]++;
    }

    result[0] /= max;
    result[1] /= max;
    result[3] = (100 * result[3]) / max;
}

int main (int argc, char *argv[])
{
    int quant_hab;
    float resultados[4] = {0};

    scanf("%d", &quant_hab);

    habi_t *hab = malloc(quant_hab * sizeof(habi_t));
    le_dados(quant_hab, hab, resultados);

    printf("%.2f\n%.2f\n%.2f\n%.2f\n", resultados[0], resultados[1], resultados[2], resultados[3]);

    free(hab);
    return 0;
}

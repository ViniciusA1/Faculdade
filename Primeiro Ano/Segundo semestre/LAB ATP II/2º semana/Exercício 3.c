#include <stdio.h>
#define prod 10
#define armz 5

int main()
{
    int i, j = 0, quant_prod[prod][armz];
    float precos[prod];

    for(i = 0; i < prod; i++) {
        printf("Produto %d: ", i + 1);
        scanf("%f", &precos[i]);
    }

    for(i = 0; i < prod; i++) {
        for(j = 0; j < armz; j++) {
            printf("Armazém %d | Produto %d: ", j + 1, i + 1);
            scanf("%d", &quant_prod[i][j]);
        }
    }

    
}
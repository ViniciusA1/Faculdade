#include <stdio.h>
#define max 10

typedef struct pessoa {
    int idade;
    float peso, altura;
} p_st;

int main()
{
    p_st cad[max];
    int i, quant_b = 0, quant_c = 0, quant_d = 0;
    float media = 0;

    for(i = 0; i < max; i++) {
        printf("Idade: ");
        scanf("%d", &cad[i].idade);
        printf("Peso: ");
        scanf("%f", &cad[i].peso);
        printf("Altura: ");
        scanf("%f", &cad[i].altura);

        media += cad[i].idade;
        if(cad[i].peso > 90 && cad[i].altura < 1.5)
            quant_b++;
        if(cad[i].altura > 1.90) {
            quant_c++;
            if(cad[i].idade < 30 && cad[i].idade > 10)
                quant_d++;
        }
    }

    printf("a) Média das idades: %.2f\n", media / max);
    printf("b) Quantidade de pessoas com peso superior a 90 quilos e altura inferior a 1.50 m: %d\n", quant_b);
    printf("c) Porcentagem com idade entre 10 e 30 anos entre as que medem mais de 1.90 m: %.2f%%\n", (float)(quant_d * 100) / quant_c);

    return 0;
}
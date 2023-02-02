#include <stdio.h>
#define max 10

int main()
{
    char sexo, resp;
    int i, resp_sim = 0, mulher_sim = 0, homem_sim = 0, total_homem = 0;

    for(i = 0; i < max; i++) {
        printf("Sexo: ");
        scanf(" %c", &sexo);
        printf("Resposta (S - Sim / N - Não): ");
        scanf(" %c", &resp);

        if(resp == 'S' || resp == 's') {
            resp_sim++;
            if(sexo == 'F' || sexo == 'f')
                mulher_sim++;
            else 
                homem_sim++;
        }

        if(sexo == 'M' || sexo == 'm')
            total_homem++;
    }

    printf("a) %d pessoas\nb) %d pessoas\nc) %d mulheres\nd) %.2f%% dos homens\n", resp_sim, max - resp_sim, mulher_sim, 100.00*(total_homem - homem_sim) / total_homem);

    return 0;
}
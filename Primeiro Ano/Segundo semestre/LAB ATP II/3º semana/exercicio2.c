#include <stdio.h>

float realiza_op(int vet[], char op)
{
    switch(op) {
        case '+': return vet[0] + vet[1];
        case '-': return vet[0] - vet[1];
        case '/': return (float) vet[0] / vet[1];
        case '*': return vet[0] * vet[1];
        default: return 0; // Erro de operação!
    }
}

int main (int argc, char *argv[])
{
    int vet_num[2];
    char operacao;
    float res;

    scanf("%d %c %d", &vet_num[0], &operacao, &vet_num[1]);
    printf("%.2f", realiza_op(vet_num, operacao));

    return 0;
}

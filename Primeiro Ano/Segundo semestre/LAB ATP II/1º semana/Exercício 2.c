#include <stdio.h>
#define ano_atual 2022

int main()
{
    int ano_pessoa;

    scanf("%d", &ano_pessoa);
    ano_pessoa = ano_atual - ano_pessoa;
    printf("Anos -> %d\nMeses -> %d\nSemanas -> %d\nDias -> %d", ano_pessoa, ano_pessoa * 12, ano_pessoa * 52, ano_pessoa * 365);

    return 0;
}
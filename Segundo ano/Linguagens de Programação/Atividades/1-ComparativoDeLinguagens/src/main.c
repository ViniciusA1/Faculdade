#include <stdio.h>
#define MAX 10

double getAverage(double x, double y)
{
        return (x + y) / 2;
}

int main(int argc, char *argv[])
{
        int number;
        double number_1, number_2;
 
        // Hello World.
        puts("Hello World");

        // Calcula e mostra média.
        fputs("Digite dois valores para cálcular a média: ", stdout);
        scanf("%lf%lf", &number_1, &number_2);
        printf("Média: %.2lf\n", getAverage(number_1, number_2));

        // Vê se um número é par.
        fputs("Digite um número para verificar paridade: ", stdout);
        scanf("%d", &number);
        puts(number & 1 ? "Ímpar" : "Par");

        // Laço para contar de 0 até 10.
        printf("==Conta até %d==\n", MAX);
        for(int i = 0; i <= MAX; i++)
                printf("%d ", i);
        puts("");

        return 0;
}

#include <stdio.h>
#define NUMBERS 2

int average(int x, int y)
{
	return (x + y) / 2;
}

int main(int argc, char *argv[])
{
	int n[NUMBERS];
	printf("Digite dois numeros inteiros separados por espaço: ");
	if (scanf("%d %d", &n[0], &n[1]) != 2)
		return 1;
	printf("A media entre eles é: %d\n", average(n[0], n[1]));
	return 0;
}

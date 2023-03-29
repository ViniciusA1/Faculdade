#include <stdio.h>
#define NUMBERS 2
int main(int argc, char *argv[])
{
	int n[NUMBERS];
	printf("Digite dois numeros separados por espaço: ");
	if (scanf("%d %d", &n[0], &n[1]) != 2)
		return 1;

	for (int i = 0; i < NUMBERS; i++)
		printf("O numero %d é %s\n", n[i],
		       n[i] % 2 == 0 ? "par" : "impar");

	return 0;
}

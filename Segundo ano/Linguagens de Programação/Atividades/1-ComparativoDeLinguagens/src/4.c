#include <stdio.h>
#define NUMBERS 2
int main(int argc, char *argv[])
{
	int n[NUMBERS];
	printf("Numeros de 1 a 10: \n");
	for (int i = 1; i <= 10; i++)
		printf("%d  ", i);
	puts("");

	return 0;
}

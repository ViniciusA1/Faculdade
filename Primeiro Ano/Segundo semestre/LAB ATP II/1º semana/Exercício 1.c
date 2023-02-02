#include <stdio.h>
#define max(a,b) (a > b) ? a : b

int main()
{
    int x, y, z;

    scanf("%d %d %d", &x, &y, &z);
    y = max(y, z);
    printf("Maior = %d\n", max(x,y));

    return 0;
}
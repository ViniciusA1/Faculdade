#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
        srand(time(NULL));
        FILE *writing_pointer = fopen("input.txt", "w");
        int number_of_elements, i;

        printf("Range: ");
        scanf("%d", &number_of_elements);
        fprintf(writing_pointer, "%d\n", number_of_elements);

        for(i = 0; i < number_of_elements; i++)
                fprintf(writing_pointer, "%d\n", rand() % number_of_elements);

        fclose(writing_pointer);
}

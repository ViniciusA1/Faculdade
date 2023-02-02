#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int *arr, int max)
{
        int aux;

        for(int i = 1; i < max; i++) {
                for(int j = 0; j < max-1; j++) {
                        if(arr[j] > arr[j+1]) {
                                aux = arr[j];
                                arr[j] = arr[j+1];
                                arr[j+1] = aux;
                        }
                }
        }
}

void print_arr(int *arr, int max)
{
        for(int i = 0; i < max; i++)
                printf("%d ", arr[i]);
        puts("");
}

int main()
{
        int *arr, max_size;

        printf("Max size: ");
        scanf("%d", &max_size);
        arr = malloc(max_size * sizeof(int));

        for(int i = 0; i < max_size; i++)
                scanf("%d", &arr[i]);

        print_arr(arr, max_size);
        bubble_sort(arr, max_size);
        print_arr(arr, max_size);

        free(arr);
        return 0;
}

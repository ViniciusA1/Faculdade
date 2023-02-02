#include <stdio.h>
#include <stdlib.h>

void selection_sort(int *arr, int max)
{
        int min_value, aux = 0;

        for(int i = 0, j; i < max-1; i++) {
                min_value = i;
                for(j = i+1; j < max; j++) {
                        if(arr[j] < arr[min_value])
                                min_value = j;
                }

                if(i != j) {
                        aux = arr[min_value];
                        arr[min_value] = arr[i];
                        arr[i] = aux;
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

        for(int i = 0; i < max_size; i++)
                scanf("%d", &arr[i]);

        print_arr(arr, max_size);
        selection_sort(arr, max_size);
        print_arr(arr, max_size);


        free(arr);
        return 0;
}

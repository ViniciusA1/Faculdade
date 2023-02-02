#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int *arr, int max)
{
        int key;

        for(int i = 1, j; i < max; i++) {
                key = arr[i];

                for(j = i; j > 0 && arr[j-1] > key; j--)
                        arr[j] = arr[j-1];

                arr[j] = key;
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
        insertion_sort(arr, max_size);
        print_arr(arr, max_size);

        
        return 0;
}


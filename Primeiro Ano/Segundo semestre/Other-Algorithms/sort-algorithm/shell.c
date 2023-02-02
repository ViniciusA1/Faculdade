#include <stdio.h>
#include <stdlib.h>

void shell_sort(int *arr, int max)
{
        int K = 1, key;

        while(K <= (max-1) / 2) K *= 2;

        while(K > 1) {
                K /= 2;

                for(int i = K, j; i < max; i++) {
                       key = arr[i];

                       for(j = i; j >= K && arr[j-K] > key; j-=K)
                               arr[j] = arr[j-K];

                       arr[j] = key;
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
        shell_sort(arr, max_size);
        print_arr(arr, max_size);

        free(arr);
        return 0;
}

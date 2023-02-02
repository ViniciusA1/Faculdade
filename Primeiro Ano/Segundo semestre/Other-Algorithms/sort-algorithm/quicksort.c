#include <stdio.h>
#include <stdlib.h>

void print_arr(int *arr, int max)
{
        for(int i = 0; i < max; i++)
                printf("%d ", arr[i]);
        puts("");
}

void change(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

void quick_sort(int *arr, int left, int right)
{
        int pivo = right, bigger = left;
        if(left >= right)
                return;

        for(int i = left; i < right; i++) {
                if(arr[i] < arr[pivo]) {
                        change(&arr[i], &arr[bigger]);
                        bigger++;
                }
        }

        change(&arr[bigger], &arr[pivo]);
        quick_sort(arr, left, pivo-1);
        quick_sort(arr, pivo+1, right);
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
        quick_sort(arr, 0, max_size-1);
        print_arr(arr, max_size);

        free(arr);
        return 0;
}

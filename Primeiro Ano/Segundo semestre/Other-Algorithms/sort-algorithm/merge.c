#include <stdio.h>
#include <stdlib.h>

void merge_array(int *arr, int l, int r, int m)
{
        int aux_1[m-l+1], aux_2[r-m], i, j, k = l;

        for(i = 0; i < m-l+1; i++)
                aux_1[i] = arr[l+i];
        for(i = 0; i < r-m; i++)
                aux_2[i] = arr[m+1+i];

        i = j = 0;
        while(i < m-l+1 && j < r-m) {
                if(aux_1[i] <= aux_2[j]) {
                        arr[k] = aux_1[i];
                        i++;
                }
                else {
                        arr[k] = aux_2[j];
                        j++;
                }

                k++;
        }

        while(i < m-l+1) {
                arr[k] = aux_1[i];
                i++, k++;
        }

        while(j < r-m) {
                arr[k] = aux_2[j];
                j++, k++;
        }
}

void merge_sort(int *arr, int left, int right)
{
        int half = (left + right) / 2;
        if(left >= right) return;


        merge_sort(arr, left, half);
        merge_sort(arr, half+1, right);

        merge_array(arr, left, right, half);
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
        merge_sort(arr, 0, max_size-1);
        print_arr(arr, max_size);

        free(arr);
        return 0;
}


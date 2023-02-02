#include <stdio.h>
#include <stdlib.h>

int binary_search(int *arr, int left, int right, int target)
{
        if(arr[left] == target) 
                return left;
        if(arr[right] == target) 
                return right;

        for(int half = (left + right) / 2; left <= right; half = (left + right) / 2) {
                if(arr[half] == target) 
                        return half;
                
                if(arr[half] > target) 
                        right = half - 1;
                else if(arr[half] < target) 
                        left = half + 1;
        }

        return -1;
}

int main()
{
        int wish, *arr, max_size, index;

        printf("Max size: ");
        scanf("%d", &max_size);
        arr = malloc(max_size * sizeof(int));
        
        for(int i = 0; i < max_size; i++)
                scanf("%d", &arr[i]);

        printf("Wish value: ");
        scanf("%d", &wish);

        index = binary_search(arr, 0, max_size-1, wish);

        if(index != -1)
                printf("Index of %d: %d\n", wish, index);
        else
                puts("Error!");

        free(arr);
        return 0;
}

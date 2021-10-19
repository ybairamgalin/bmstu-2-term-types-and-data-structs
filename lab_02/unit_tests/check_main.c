#include "../inc/subscriber.h"

int cmp(const void* a, const void* b)
{
    int *first = (int*)a;
    int *second = (int*)b;

    return *first - *second;
}

int main(void)
{
    {
        int arr[9] = { 3, 7, 8, 5, 2, 1, 9, 5, 4};
        int keys[9];

        for (int i = 0; i < 9; i++)
            keys[i] = i;

        my_sort_key(arr, keys, 9, sizeof(int), cmp);

        for (int i = 0; i < 9; i++)
            printf("arr[%d] = %d\n", keys[i], arr[keys[i]]);

        printf("\n");
    }

    {
        int arr[9] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        int keys[9];

        for (int i = 0; i < 9; i++)
            keys[i] = i;

        my_sort_key(arr, keys, 9, sizeof(int), cmp);

        for (int i = 0; i < 9; i++)
            printf("arr[%d] = %d\n", keys[i], arr[keys[i]]);
    }
}
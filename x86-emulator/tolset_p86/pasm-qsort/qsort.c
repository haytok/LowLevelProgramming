#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int main(int argc, char *argv[])
{
    int arr[] = {3, 2, 5, 4, 1};
    int i;
    qsort(arr, 5, sizeof(int), cmp);
    for (i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}

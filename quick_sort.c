#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int rand_data(int **list, int size, int range)
{
    if (size <= 0) return -1;
    
    int i, *data = (int*) calloc(size, size*sizeof(int));
    if (!data) return -1;

    if (range <= 0) {
        for (i = 0; i < size; i++) 
            data[i] = rand();
    } else {
        for (i = 0; i < size; i++) 
            data[i] = (rand() % range);
    }
    *list = data;
    return 0;
}

void dump(int *list, int size)
{
    int i;
    printf("{");
    for (i = 0; i < size; i++) printf(" %d", list[i]);
    printf("}\n");
}

void swap(int *a, int i, int j)
{
    int temp;
    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

/* sorting a[left:right] */
void quickSort(int *a, int left, int right)
{
    int pivot, i, j;
    if (left < right) {
        i = left;
        j = right + 1;
        pivot = a[left];
        do {
            do i++; while((i <= right) && (a[i] < pivot));
            do j--; while((j >= left) && (a[j] > pivot));
            if (i < j) swap(a, i, j);
        } while (i < j);
        swap(a, left, j);
        quickSort(a, left, j-1);
        quickSort(a, j+1, right);
    }
}

int main(void)
{
    int len, range, i, ret, *list = NULL;
    clock_t start, end;
    float latency;

    printf("please input list size:");
    if (scanf("%d", &len) != 1) return -1;

    printf("please input max random number or -1 for no range:");
    if (scanf("%d", &range) != 1) return -1;

    printf("generating random data\n");
    if (rand_data(&list, len, range) != 0) {
        printf("failed to generate random data\n");
        ret = -1;
        goto exit;
    }
    if (len < 500) dump(list, len);

    printf("start quick sorting\n");
    start = clock();
    quickSort(list, 0, len-1);
    end = clock();

    latency = (((float)end - (float)start)/1000000.0F) * 1000;
    printf("quick sort execution time %f ms\n", latency);
    if (len < 500) dump(list, len);
    ret = 0;

exit:
    if (list) free(list);
    return ret;
}

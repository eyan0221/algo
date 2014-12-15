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
int min(int x, int y)
{
    return (x < y) ? x : y;
}

void merge(int *data, int left, int middle, int right, int *tmp)
{
    int l, r, i;
    l = left;
    r = middle;
    i = left;
    while (i < right) {
        tmp[i++] = ((l < middle) && ((r >= right) ||  (data[l] <= data[r]))) 
                    ? data[l++]
                    : data[r++];                
    }
    
    for (i = left; i < right; i++) {
        data[i] = tmp[i];
    }
}

int mergeSort(int *a, int size)
{
    int *tmp = NULL;
    int width, i;

    if (!a) return -1;

    tmp = (int*)calloc(size, size*sizeof(int));
    if (!tmp) return -1;

    for (width = 1; width < size; width *= 2) {
        for (i = 0; i < size; i += 2*width) {
            merge(a, i, min(i + width, size), min(i + 2 * width, size), tmp);
        }
    }

    if (tmp) free(tmp);
    return 0;
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

    printf("start merge sorting\n");
    start = clock();
    mergeSort(list, len);
    end = clock();

    latency = (((float)end - (float)start)/1000000.0F) * 1000;
    printf("merge sort execution time %f ms\n", latency);
    if (len < 500) dump(list, len);
    ret = 0;

exit:
    if (list) free(list);
    return ret;
}

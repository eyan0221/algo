#include <stdio.h>
#include <stdlib.h>

void generate(long *a, long size, long range)
{
    long i;
    for (i = 0; i < size; i++) {
        a[i] = (range > 1) ? (long)rand() % range : (long)rand();
    }
}

void dump(long *a, long size)
{
    long i = 0;
    printf("{");
    while (i < size) {
        printf(" %lu", a[i++]);
    }
    printf("}\n");
}

void insertionSort(long *a, long size)
{
    long i, j, temp;

    for (i = 1; i < size; i++) {
        temp = a[i];
        j = i - 1;
        while ((j >= 0) && (a[j] > temp)) {
            a[j + 1] = a[j];
            j--;
        }
        a[++j] = temp;
    }
}

long input(char *s)
{
    long x;
    printf("%s", s);
    if (scanf("%ld", &x) != 1) return -1;
    return x;
}

int main(void)
{
    long size, range;
    long *list = NULL;
        
    size = input((char*)"please input list size or -1 to exit program\n");
    if (size <= 0) return 0;

    range = input((char*)"please input an integer for random number range or -1 to exit program\n");
    if (range <= 0) return 0;

    list = (long*)calloc(size, size*sizeof(long));
    if (!list) {
        printf("failed to allocate memory for list[%lu]\n", size);
        return -1;
    }

    generate(list, size, range);
    printf("generating random list[%lu]\n", size);
    dump(list, size);

    printf("start insertion soritng\n");
    insertionSort(list, size);
    dump(list, size);

    if (list) free(list);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

struct two_sum {
    long x;
    long y;
};

int ts_fun1(long *a, long size, long sum, struct two_sum *ts) {
    long i, j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (( i != j) && ((a[i] + a[j]) == sum)) {
                ts->x = i;
                ts->y = j;
                return 0;
            }
        }
    }
    return -1;
}

void dump(long *array, long size) 
{
    long i;
    printf("{");
    for (i = 0; i < size; i++) {
        printf(" %ld", array[i]);
    }
    printf("}\n");
}

int gen_random_array(long **a, long size, long range) 
{
    long i;
    long *array = (long *)calloc(size, size*sizeof(long));
    if (!array) return -1;
   
    for (i = 0; i < size; i++) {
        array[i] = (range > 1) ? (long) (rand() % range) : (long)rand();
    }
    dump(array, size);

    *a = array;
    return 0;
}

int input_long(long *in, char *s)
{
    printf("%s\n", s);
    int ret = scanf("%ld", in);
    if (ret != 1) printf("invalid input\n");
    return ret;
}

int main(void)
{
    long *array = NULL;
    long size, range, sum;
    struct two_sum *ts = (struct two_sum*) calloc(1, sizeof(struct two_sum));

    if ((input_long (&size, (char *)"please input array size") != 1) || (size < 0)) return -1;
    if (input_long (&range, (char *)"please input range of array elements") != 1) return -1;
    if (input_long (&sum, (char *)"please input the sum of two array elements") != 1) return -1;

    if (gen_random_array(&array, size, range) != 0) 
        return -1;

    if (!ts_fun1(array, size, sum, ts)) {
        printf("array[%ld] + array[%ld] = %ld\n", ts->x, ts->y, sum);
    } else {
        printf("failed to get the two number\n");
    }

    if (ts) free(ts);
    if (array) free(array);

    return 0;
}

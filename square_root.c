#include <stdio.h>
#include <stdlib.h>

/* 
 * the number of times to call the mid function will be 
 * smaller than or equal to log2(n) when input number is n.
 */
long mid(long start, long end)
{
    /* caution: (start+end)/2 may lead to overflow */
    return (start + (end-start)/2);
}

/*
 * Input: a 64 bits integer n
 * Return: the floor of square root of n
 */
long square_root(long in)
{
    long out, tmp, start, end;

    /* avoid segmentation fault caused by dividing zero */
    if (in <= 1) return in;

    start = 0;
    end = in;
    do {
        out = mid(start, end); 
        tmp = (double) in/out;  
        
        /* caution: compare in and out*out may lead to overflow */
        if (tmp == out) {  
            break;
        } else if (tmp < out) {
            end = out;
        } else {
            start = out;
        }
    } while ((end - start) >= 2);
    out = mid(start, end); 

    return out;
}

int main(void)
{
    long input, output;

    do {
        printf("please input a positive integer\n");
        if (scanf("%ld", &input) != 1) return -1;
        
        output = square_root(input);
        if (output >= 0) {
            printf("square root of %ld is %ld\n", input, output);
        }
    } while (input > 0);

    return 0;
}

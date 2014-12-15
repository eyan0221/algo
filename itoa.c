#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int itoa_func(int input, char **string)
{
    int i, sign, temp, size;
    char *s = NULL;

    if ((sign = input) < 0) input = -input;
    temp = input;
    size = (sign < 0) ? 1 : 0;
    while (temp > 0) { 
        size++;
        temp /= 10;
    }

    s = (char*) calloc(size, size * sizeof(char));
    if (!s) return -1;
  
    temp = input;
    i = size - 1; 
    while (temp > 0 && i >= 0) {
        s[i--] = '0' + temp % 10; 
        temp /= 10;
    }
    if (sign < 0) s[0] = '-';

    *string = s;
    return 0;
}

int main(void)
{
    int input;
    char *s = NULL;

    printf("please input an integer\n");
    if (scanf("%d", &input) != 1) return -1;

    itoa_func(input, &s);
    printf("itoa(%d)=%s\n", input, s);

    if (s) free(s);
    return 0;
}

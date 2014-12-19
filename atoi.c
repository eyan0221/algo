#include <stdio.h>
#include <stdlib.h>

/* sos: return size of a string */ 
int sos(char *s)
{
    int size;
    for (size = 0; (*s != '\0'); s++) size++;
    return size;
}

/* atoi_func: convert a string into an integer */
int atoi_func(char *s)
{
    int i, sign, temp, size = sos(s);

    if (size <= 0) return -1;
    
    i = (s[0] == '-') ? 2 : 1;
    sign = (s[0] == '-') ? -1 : 1;
    temp = s[i-1] - '0';

    while (i < size) {
        /* return -1 if overflow */
        if (temp > 2147483647) {
            temp = -1;
            sign = 1;
            break;
        }
        if (s[i] < 48 || s[i] > 57) return -1;
        temp = temp*10 + s[i++] - '0';
    }
    
    return (sign > 0) ? temp : -temp;
}

int main(void)
{
    char s[10];

    printf("please input a string of integers\n");
    if (scanf("%s", s) != 1) return -1;

    printf("atoi(%s)=%d\n", s, atoi_func(s));
    return 0;
}

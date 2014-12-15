#include <stdio.h>
#include <stdlib.h>

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval;
}

int main(void)
{
    char *s;
    unsigned inx;

    printf("please input string\n");
    if (scanf("%s", s) != 1) return -1;

    inx = hash(s);
    printf("hash index is %u for %s\n", inx, s);

    return 0;
}

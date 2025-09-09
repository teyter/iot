#include <stdio.h>
#include <string.h>

int power(int base, int exp)
{
    int x = base;
    for (int i = 0; i < exp-1; i++)
    {
        base *= x;
    }
    return base;
}

int main() 
{
    char *s;
    s = "010";
    s = "100";
    s = "0xFF";
    s = "0b1001";
    int m;
    int strl = strlen(s);
    int *numbers[strl];
    if (s[1] == 'b')
    {
        printf("%s\n", "BINARY");
        m = 2;
        /**
        for (int i = 2; i < strl; i++)
        {
            switch ()
        }
         */
    }
    else if (s[1] == 'x')
    {
        printf("%s\n", "HEX");
        m = 16;
    }
    else if (s[0] == '0')
    {
        printf("%s\n", "OCTAL");
        m = 8;
    }
    else
    {
        return 2;
    }
    int e = strl - 1;
    printf("e: %d\n", e);
    int sum = 0;
    for (int i = 0; i < strl; i++)
    {
        sum += (s[i]-48) * power(m, e);
        printf("sum += %d * %d^%d\n", (int)s[i], m, e);
        e--;
    }
    printf("%d\n",sum); 
    return 0;
}
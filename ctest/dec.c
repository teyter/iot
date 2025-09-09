#include <stdio.h>
#include <string.h>

int power(int base, int exp)
{
    if (exp == 0) return 1;
    int x = base;
    for (int i = 0; i < exp-1; i++)
    {
        base *= x;
    }
    return base;
}

int bconvert(char *s)
{
    int base;
    int e;
    int len = strlen(s);
    int j = 2;
    if (s[1] == 'b') {base = 2; e = len-3;} else if (s[1] == 'x') {base = 16;e=len-3;} else {base = 8;e=len-2;j=1;}
    int sum = 0;
    for (int i = j; i < len; i++)
    {
        if (s[i] == '0')
        {
            sum += 0 * power(base, e);
        } 
        else if (s[i] == '1')
        {
            sum += 1 * power(base, e);
        }
        else if (s[i] == '2')
        {
            sum += 2 * power(base, e);
        }
        else if (s[i] == '3')
        {
            sum += 3 * power(base, e);
        }
        else if (s[i] == '4')
        {
            sum += 4 * power(base, e);
        }
        else if (s[i] == '5')
        {
            sum += 5 * power(base, e);
        }
        else if (s[i] == '6')
        {
            sum += 6 * power(base, e);
        }
        else if (s[i] == '7')
        {
            sum += 7 * power(base, e);
        }
        else if (s[i] == '8')
        {
            sum += 8 * power(base, e);
        }
        else if (s[i] == '9')
        {
            sum += 9 * power(base, e);
        }
        else if (s[i] == 'A')
        {
            sum += 10 * power(base, e);
        }
        else if (s[i] == 'B')
        {
            sum += 11 * power(base, e);
        }
        else if (s[i] == 'C')
        {
            sum += 12 * power(base, e);
        }
        else if (s[i] == 'D')
        {
            sum += 13 * power(base, e);
        }
        else if (s[i] == 'E')
        {
            sum += 14 * power(base, e);
        }
        else if (s[i] == 'F')
        {
            sum += 15 * power(base, e);
        }
        e--;
    }
    return sum;
}

int main() 
{
    char *s;
    s = "100";
    s = "0xFF";
    s = "0b1111";
    s = "0765";
    bconvert(s);
    return 0;
}

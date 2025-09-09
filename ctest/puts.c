#include <stdio.h>

int main(void) {
    int x = 5;
    char s[64];                     // make a buffer big enough
    snprintf(s, sizeof s, "number is %d", x);
    puts(s);
    return 0;
}

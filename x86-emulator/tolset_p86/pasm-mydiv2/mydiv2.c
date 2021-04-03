#include <stdio.h>

void mydiv2(int a, int b, int quot, int rem)
{
    quot = a / b;
    rem = a % b;
}

int main(void)
{
    int q = 0, r = 0;
    mydiv2(10, 3, q, r);
    printf("q == %d, r == %d\n", q, r);
    return 0;
}

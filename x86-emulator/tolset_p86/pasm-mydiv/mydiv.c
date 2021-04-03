#include <stdio.h>

void mydiv(int a, int b, int *quot, int *rem)
{
    *quot = a / b;
    *rem = a % b;
}

int main(void)
{
    int q, r;
    mydiv(10, 3, &q, &r);
    printf("q == %d, r == %d\n", q, r);
    return 0;
}

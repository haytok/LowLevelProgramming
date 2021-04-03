#include <stdio.h>

size_t my_strlen(const char* s)
{
    static int count = 0;
    size_t i;
    
    count++;
    printf("strlen: called %d time.\n", count);
    
    for (i = 0; s[i]; i++);
    return i;
}

int main(void)
{
    printf("%d\n", my_strlen("foobar"));
    return 0;
}

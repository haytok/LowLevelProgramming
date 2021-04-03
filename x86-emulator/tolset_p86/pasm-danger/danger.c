void func()
{
    int *ptr;
    ptr = (int *)0x100;
    *ptr = 41;
}

int main(void)
{
    func();
    return 0;
}

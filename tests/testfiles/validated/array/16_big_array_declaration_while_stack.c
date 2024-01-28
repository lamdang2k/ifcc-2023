int foo()
{
    return 2;
}
int main()
{
    int a [100000];
    int b = 0;
    int i = 0;
    while(i < 100)
    {
        a[i] = foo();
        i = i+1;
    }

    return b;
}
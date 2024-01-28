int foo()
{
    return 2;
}
int main()
{
    int a [100000];
    int b [100000];
    int i = 0;
    while(i < 100)
    {
        a[i] = foo();
        b[i] = foo();
        i = i+1;
    }

    return b[50];
}
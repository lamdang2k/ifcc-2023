int main ()
{
    int a = 6;
    int b = 10;
    if(a+b>a){
        a = a-b;
    } else{
        return a*b;
        b=4*b;
    }
    return a;
}
int fibo(int n){
    if ( n <= 0 )
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }else{
        /*return a-b;*/
        return fibo(n-1) + fibo(n-2);
    }
}
int main(){
    return 2*fibo(8);
}
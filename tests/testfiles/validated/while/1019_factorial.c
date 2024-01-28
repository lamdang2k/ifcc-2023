int factorial(int n){
    int i=1;
    int f = i;
    while (i<=n){
        f=f*i;
        i = i+1;
    }
    return f;
}
int main(){
    return 2*factorial(8);
}
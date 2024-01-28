void foo(int a, int b); 

int main (){
  int y = foo(3,10); 
  return y; 
}
int hoo(int c,int d);
void foo (int a, int b){
    return a+b+hoo(a*4*b,2*a+2*b);
}
int hoo(int c,int d){
  int x = c-d;
  return x;
}
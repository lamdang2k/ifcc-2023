int foo(int a, int b); 

int main (){
  int a,b,c,d;
  int y = foo(3,10); 
  return y; 
}
int hoo(int c,int d);
int foo (int a, int b,int c){
    return a+b+c+hoo(a*4*b,2*a+2*b);
}
int hoo(int c,int d){
  int x = c-d;
  return x;
}
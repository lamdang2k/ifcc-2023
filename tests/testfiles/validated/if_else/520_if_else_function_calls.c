int foo(int a, int b); 
int hoo(int c,int d,char e);
int main (){
  int a=10,b=a;
  int y = foo(a,b); 
  if (y>a){
    char c = 'c';
    int x = hoo(y,a,c);
    if (x!=y){
        return foo(x,y);
    } else{
        return foo(y,y);
    }
  }
  return y; 
}

int foo (int a, int b){
    return a+b+hoo(a*4*b,2*a+2*b,'c');
}
int hoo(int c,int d,char e){
  return c-d+e;
}
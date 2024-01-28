void foo(int a, int b); 
int hoo(int a) {
    return 2*a;
} 
int main (){
  int a,b,c;
  a = hoo(10);
  foo(3,10);
  b= hoo(a); 
  int y = 3;
  foo(a,b);
  return hoo(b,y); 
}
void foo (int a, int b){
    int x = a+b;
}
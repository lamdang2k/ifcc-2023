int foo (int a ,int b){
  return a + b;
}
int main() {
  int y = 90;
  int x = 10; 
  if(x<90){
    return x;
    x = x*3;
  }
  return foo(x,y); 
}
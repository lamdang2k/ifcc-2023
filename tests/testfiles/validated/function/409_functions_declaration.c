int foo(int a, int b); 

int main (){
  int y = foo(10,10); 
  return y; 
}

int goo();
int goo(){
  return 10;
}
int foo(int a, int b){
  return a+b+goo();
}
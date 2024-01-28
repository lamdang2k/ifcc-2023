int foo(int a, char c, char d, int b){
  int x = 10;
  return a+b+c+d;
}

int main (){
  int a = foo(3, 'A', 'B', 5);
  return a; 
}
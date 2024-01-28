int foo(int a, char b); 

int main (){
  char a = 'a';
  int y = foo(3,10);
  int z = foo(y,a); 
  return y*z; 
}

int foo (int a, char b){
    return a+b;
}

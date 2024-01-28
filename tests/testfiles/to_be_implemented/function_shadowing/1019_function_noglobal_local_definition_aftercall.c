int main (){
  int e;

  
  {int foo(int a, int b){
    return a+b;
  };
  e = foo(2,3);}


  {int foo(int a, int b){
    return a*b;
  };
  e = e + foo(2,3);}

  e = e + foo(2,3);

  return e; 
}
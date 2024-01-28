int foo(int a, int b){
    return a+b;
}; 

int main (){
  int e;

  
  {
  e = foo(2,3);}


  {
  e = e + foo(2,3);}

  e = e + foo(2,3);

  return e; 
}
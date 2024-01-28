int foo();

int foo(){
  return 4;
}

int main (){
  int a = foo();
  /* doesn't work : function call does nothing (declaration 'a = expr' expects an elt on the stack)*/
  return 5; 
}
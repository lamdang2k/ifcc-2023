int foo(int a, int b);
int goo();
int goo(){
  return 10;
}
int foo(int a, int b){
  return a+b+goo();
}
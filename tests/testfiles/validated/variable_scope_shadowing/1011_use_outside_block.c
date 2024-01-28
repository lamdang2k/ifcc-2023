int main (){
  int a;

  {int b = 5;
  a = b;}

  a = a + b;

  return a; 
}
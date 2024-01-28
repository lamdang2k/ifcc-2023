int main (){
  int a = 3;
  int b;

  {b = a+1;
  a = b*7;
  int a = a + 1;
  a = b*3 + a*2;}

  return a; 
}
int main (){
  int a = 3;

  {int b = 5;
  a = a+b*2;}

  return a; 
}
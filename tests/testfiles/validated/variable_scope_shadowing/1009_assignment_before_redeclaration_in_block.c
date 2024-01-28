int main (){
  int a = 3;
  int b;

  {b = a+1;
  a = b*7;
  int a;
  a = b*3;}

  return a; 
}
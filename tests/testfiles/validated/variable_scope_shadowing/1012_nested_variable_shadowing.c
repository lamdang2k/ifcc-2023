int main (){
  int a = 0;
  int e = 10;
  {
    int e = 5;
    {
      int e = 7;
      {
        int e = 11;
        a = a + e;
      }
      a = a +e;
      {
        a = a + e;
        int e = 1;
        a = a + e;
      }
    }
    a = e + a;
  }
  a = a + e;

  return a; 
}
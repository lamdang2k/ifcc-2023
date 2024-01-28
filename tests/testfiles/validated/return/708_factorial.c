int factorial(int n);
 
int main()
{
  int x = factorial(4);
  return x+factorial(x*2);
}
int factorial(int n)
{
  if (n == 0) 
    return 1;
  else
    return (n*factorial(n-1));
}
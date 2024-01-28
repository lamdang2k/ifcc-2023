int foo(int a, int b,char c, char d, int e, int f, char g){return a-b+c*d-e*(g+f);}

int main ()
{
	int a = foo(1,2,'a','b',3,4,'c');
	return a;
}

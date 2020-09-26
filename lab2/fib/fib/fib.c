#include<stdio.h>

int Fib(int n)
{
	if (n == 1)
	{
		return 0;
	}
	if (n == 2)
	{
		return 1;
	}
	int f1 = 0;
	int f2 = 1;
	int c = 0;
	for (int i = 3; i <= n; i++)
	{
		c = f1 + f2;
		f1 = f2;
		f2 = c;
	}

	return c;
}


int main()
{
	int n;
	scanf_s("%d", &n);
	getchar();
	int ret = Fib(n);
	printf("%d", ret);
	system("pause");
	return 0;
}
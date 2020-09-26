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
	return Fib(n - 1) + Fib(n - 2);
}

int main()
{
	int n;
	scanf_s("%d", &n);
	int ret = Fib(n);
	printf("%d", ret);
	system("pause");
	return 0;
}
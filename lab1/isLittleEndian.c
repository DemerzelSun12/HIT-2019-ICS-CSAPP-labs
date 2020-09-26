#include<stdio.h>


int isLittleEndian()
{
	int a = 1;
	return (*(char*)& a);
}
int main()
{
	int b = isLittleEndian;
	if (b)
		printf_s("是小端机器。");
	else
		printf_s("是大端机器。");
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>

#define EPS 1e-11

char* cs_itoa(int ia,char* os)
{

	int i = 0; 
	if (ia < 0) 
	{
		ia = -ia;
		os[i++] = '-';
	}
	do
	{
		os[i++] = ia % 10 + 48;		//0的ASCII码为48 
		ia /= 10;	
	} while (ia);

	os[i] = '\0';
	int j = 0;
	if (os[0] == '-')
	{
		j = 1;
		++i; 
	}
	for (; j < i / 2; j++)
	{
		os[j] = os[j] + os[i - 1 - j];
		os[i - 1 - j] = os[j] - os[i - 1 - j];
		os[j] = os[j] - os[i - 1 - j];
	}

	return os;
}

char* cs_ftoa(double id, char* os, int m)
{
	int integer;
	double decimal;
	int i = 0;
	if (id < 0)
	{
		os[i] = '-';
		i++;
		id = -id;
	}
	integer = (int)id;
	decimal = id - integer;


	while (integer > 0) 
	{
		os[i] = '0' + integer % 10;
		i++;
		integer /= 10;
	}

	id -= (int)id;
	double tp = 0.1;
	os[i] = '.';
	i++;
	for (int j=1 ; j<=m ;j++) 
	{
		id -= tp * (int)(decimal * 10);
		tp /= 10;
		os[i] = '0' + (int)(decimal * 10);
		i++;
		decimal = decimal * 10.0 - (int)(decimal * 10);
	}
	os[i] = '\0';

}

int main()
{
	int i;
	int ia;
	int num;
	double id;
	char os[30]="";
	printf_s("输入1，执行itoa，输入2，执行ftoa\n");
	scanf_s("%d", &i);
	getchar();
	switch (i)
	{
	case 1:
		scanf_s("%d", &ia);
		cs_itoa(ia, os);
		printf_s("%s", os);
		break;
	case 2:
		scanf_s("%lf",&id);
		printf_s("小数点后保留位数：");
		scanf_s("%d", &num);
		cs_ftoa(id, os, num);
		printf_s("%s", os);
		break;
	default:
		break;
	}
	return 0;
}
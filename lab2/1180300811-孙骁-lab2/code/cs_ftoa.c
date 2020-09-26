#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EPS 1e-3

void cs_ftoa(double id, char* os, int m)
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
	for (int j = 1; j <= m; j++)
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
	int m;
	double id;
	char os[30] = "";
	scanf_s("%lf", &id);
	printf("请输入小数点保留位数");
	scanf_s("%d", &m);
	cs_ftoa(id, os, m);
	printf_s("%s", os);
}
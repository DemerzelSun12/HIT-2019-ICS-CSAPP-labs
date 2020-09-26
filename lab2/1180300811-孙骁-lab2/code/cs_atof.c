#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>

double cs_atof(char* str)
{
	double n = 0, sign = 1, scale = 0;
	int subscale = 0, signsubscale = 1;

	//负数
	if (*str == '-') {
		sign = -1, str++;
	}

	while (*str == '0') {
		str++;
	}

	if (*str >= '1' && *str <= '9') {
		do {
			n = (n * 10.0) + (*str - '0');
			str++;
		} while (*str >= '0' && *str <= '9');	//读取整数部分
	}

	if (*str == '.' && str[1] >= '0' && str[1] <= '9') {
		str++;
		do {
			n = (n * 10.0) + (*str - '0');
			scale--;
			str++;
		} while (*str >= '0' && *str <= '9');	//读取小数部分
	}

	//可能存在指数部分
	if (*str == 'e' || *str == 'E') {
		str++;
		if (*str == '+') {
			str++;
		}
		else if (*str == '-') {
			signsubscale = -1, str++;
		}

		while (*str >= '0' && *str <= '9')
		{
			subscale = (subscale * 10) + (*str++ - '0');
		}
	}
	n = sign * n * pow(10.0, (scale + subscale * signsubscale));
	return n;
}

int main()
{
	char* p;
	int i, j;
	int s_to_int;
	double s_to_double;
	printf("Input the length:");
	scanf_s("%d", &i);
	getchar();
	p = (char*)malloc(sizeof(char) * i);
	for (int j = 0; j <= i; j++)
	{
		scanf_s("%c", &p[j]);
	}
	p[i + 1] = '\0';
	getchar();
	s_to_double = cs_atof(p);
	printf_s("%lf", s_to_double);
	return 0;
}
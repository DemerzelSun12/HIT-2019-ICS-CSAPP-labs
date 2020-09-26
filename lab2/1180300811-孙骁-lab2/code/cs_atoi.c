#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>

int cs_atoi(char* str)
{
	int a = 0;
	int state;
	if (*str == '-')
	{
		state = -1;
		while (*(++str) != '\0')
		{
			a = a * 10 + (*str - '0');
		}
	}
	else
	{
		state = 1;
		while (*str != '\0')
		{
			a = a * 10 + (*str - '0');
			str++;
		}
	}

	return state * a;
}

int main()
{
	char* p;
	int i, j;
	int s_to_int;
	double s_to_float;
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
	s_to_int = cs_atoi(p);
	printf_s("%d", s_to_int);
	return 0;
}
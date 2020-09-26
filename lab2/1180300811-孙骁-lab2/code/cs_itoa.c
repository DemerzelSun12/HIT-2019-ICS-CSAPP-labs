#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>

char* cs_itoa(int ia, char* os)
{

	int i = 0;
	if (ia < 0)
	{
		ia = -ia;
		os[i++] = '-';
	}
	do
	{
		os[i++] = ia % 10 + 48;		//0µÄASCIIÂëÎª48 
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


int main()
{
	int i;
	int ia;
	int num;
	double id;
	char os[30] = "";
	scanf_s("%d", &ia);
	cs_itoa(ia, os);
	printf_s("%s", os);
	return 0;
}
#include<stdio.h>

char cstr[100] = "1180300811-����";
char* pstr = "1180300811-����";
int main()
{
	*cstr = "230601200006267134";
	*pstr = "230601200006267134";
	printf("%s", cstr);
	printf("%s", pstr);
	return 0;
}
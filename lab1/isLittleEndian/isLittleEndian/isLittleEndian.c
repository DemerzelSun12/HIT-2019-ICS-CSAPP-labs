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
		printf_s("��С�˻�����");
	else
		printf_s("�Ǵ�˻�����");
	return 0;
}
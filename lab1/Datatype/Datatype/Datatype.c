#include<stdio.h>

typedef struct SX
{
	int i;
}SX;

typedef union Demerzel
{
	char a;
	int b;
}Demerzel;

int main()
{
	char a = 'A';
	int b = 4;
	short c = 2;
	long d = 1180300811;
	float e = 150.214;
	double f = 1.50712;
	int g[4] = { 86,626,59,221 };
	int* p = &b;
	enum lc
	{
		Sun, Mon, Tue, Wed, Thu, Fri, Sat
	}day;
	SX sx;
	sx.i = 4;
	Demerzel demerzel;
	demerzel.a = 'B';
	demerzel.b = 6;

	printf_s("类型\t内容\t地址\t16进制内存各字节\n");
	printf_s("char\t%c\t%p\t%x\n", a, &a, a);
	printf_s("int\t%d\t%p\t%x\n", b, &b, b);
	printf_s("short\t%d\t%p\t%x\n", c, &c, c);
	printf_s("long\t%d\t%p\t%x\n", d, &d, d);
	printf("float\t%f\t%p\t%x\n", e, &e, e);
	printf("double\t%lf\t%p\t%x\n", f, &f, f);
	printf_s("score\t%d,%d,%d,%d\t%p\n", g[0], g[1], g[2], g[3], g);
	printf("*\t%d\t%p\t%x\n", p, &p, p);
	printf_s("enum\t\t%p\t%x\n", &day, day);
	printf_s("struct\t%d\t%p\t%x\n", sx.i, &sx.i, sx.i);
	printf_s("union.char\t%c\t%p\t%x\n", demerzel.a, &demerzel.a, demerzel.a);
	printf_s("union.int\t%d\t%p\t%x\n", demerzel.b, &demerzel.b, demerzel.b);
	printf("%lx", main);
	printf("%lx", printf);

	return 0;
}
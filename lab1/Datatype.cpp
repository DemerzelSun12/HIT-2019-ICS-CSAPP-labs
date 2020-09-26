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

	printf("类型\t\t内容\t\t地址\t\t\t16进制内存各字节\n");
	printf("char\t\t%c\t\t%p\t%x\n", a, &a, a);
	printf("int\t\t%d\t\t%p\t%x\n", b, &b, b);
	printf("short\t\t%d\t\t%p\t%x\n", c, &c, c);
	printf("long\t\t%d\t%p\t%x\n", d, &d, d);
	printf("float\t\t%f\t%p\t%x\n", e, &e, e);
	printf("double\t\t%lf\t%p\t%x\n", f, &f, f);
	printf("score\t\t%d,%d,%d,%d\t%p\n", g[0], g[1], g[2], g[3], g);
	printf("*\t\t%d\t\t%p\t%x\n", p, &p, p);
	printf("enum\t\t\t\t%p\t%x\n", &day, day);
	printf("struct\t\t%d\t\t%p\t%x\n", sx.i, &sx.i, sx.i);
	printf("union.char\t%c\t\t%p\t%x\n", demerzel.a, &demerzel.a, demerzel.a);
	printf("union.int\t%d\t\t%p\t%x\n", demerzel.b, &demerzel.b, demerzel.b);
	printf("main\t\t\t\t\t\t\t%lx\n", main);
	printf("printf\t\t\t\t\t\t\t%lx\n", printf);

	return 0;
}

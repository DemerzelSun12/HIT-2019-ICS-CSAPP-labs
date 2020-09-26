#include <stdio.h>

int main(void)
{
	union
	{
		float f;
		unsigned int n;
	} x;

	x.n = 0x00000000;
	printf("+0 = %.50f\n", x.f);

	x.n = 0x80000000;
	printf("-0 = %.50f\n", x.f);

	x.n = 0x00000001;
	printf("min postive = %.50f\n", x.f);

	x.n = 0x7f7fffff;
	printf("max positive = %.50f\n", x.f);

	x.n = 0x00800000;
	printf("min positive denormalized = %.50f\n", x.f);

	x.n = 0x7f800000;
	printf("+infinity = %.50f\n", x.f);

	x.n = 0x7f800233;
	printf("Nan = %.50f\n", x.f);

	return 0;
}
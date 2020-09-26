#include <stdio.h>

int main()
{
	float f = 10.26;
	printf("%f\n", f / 0.0);
	printf("%f\n", f / 1e-50);
	return 0;
}
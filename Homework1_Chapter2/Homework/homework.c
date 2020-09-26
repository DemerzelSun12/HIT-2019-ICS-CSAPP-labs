#include<stdio.h>
typedef unsigned float_bits;

float_bits float_twice(float_bits f)
{
	unsigned sign = f >> 31;
	unsigned exp = (f >> 23) & 0xff;
	unsigned frac = f & 0x7fffff;

	if (exp == 0xff)
	{
		return f;
	}
	else if (exp == 0)
	{
		frac <<= 1;
	}
	else if (exp == 0xfe) 
	{
		exp = 0xff;
		frac = 0;
	}
	else 
	{
		exp++;
	}
	return (sign << 31) | ((exp) << 23) | (frac);
}

int main()
{
	float_bits f;
	scanf_s("%u", &f);
	float_bits ff = float_twice(f);
	printf("%u", ff);
	return 0;
}
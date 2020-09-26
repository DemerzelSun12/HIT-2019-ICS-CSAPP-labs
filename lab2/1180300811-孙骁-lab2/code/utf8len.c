#include<stdio.h>

int utf8len(char* a) {
	int i = 0;
	while (*a != '\0')
	{
		if (*a & 1 << 7)
		{
			if (*a & 1 << 6)
			{
				if (*a & 1 << 5)
				{
					if (*a & 1 << 4)
					{
						i++;
						a += 4;
						continue;
					}
					i++;
					a += 3;
					continue;
				}
				i++;
				a += 2;
				continue;
			}
		}
		i++;
		a++;
		continue;
	}
}

int main()
{
	char a[1000];
	gets(a);
	int i = utf8len(a);
	printf("¹²ÓÐ×Ö·û%d¸ö", i);
	return 0;
}
#include <stdio.h>
#include <string.h>

int main() 
{
	int x = 0;	
	while (1)
	{
		x++;
		printf("%d ", x);
		if (x > 65535) break;
	}

	printf("%d ", x);
	return 0;
}

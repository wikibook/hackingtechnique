#include <stdio.h>

#define MAX 127

int main( )
{
	int i, value[MAX];
	
	// value[] 배열에 0, 1, 2, 3, 4... 순서의 정수값으로 초기화하고 진수별로 출력
	for(i=0; i<MAX; i++)
	{
		value[i] = i;
		printf("Hex=0x%x, DEC=%d, OCT=%o, CHAR=%c\n", value[i],value[i],value[i],value[i]);
	}
	printf("\n");
}
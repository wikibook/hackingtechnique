#include <unistd.h>

int main( )
{
	int i;
	for(i=0; i<=10; i++)
	{
		system("/usr/bin/level5 &"); // 백그라운드로 프로세스 실행
	}
}
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

void shellout(void);

int main( )
{
	char string[100];
	int check;
	int x = 0;
	int count = 0;
	fd_set fds;
	
	printf(" &string:%p\n &check:%p\n &x:%p\n &count:%p \n &fds:%p\n", string, &check, &x, &count, &fds);
}
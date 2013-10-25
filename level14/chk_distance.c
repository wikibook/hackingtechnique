#include <stdio.h>
#include <unistd.h>

int main( )
{
	int crap;
	int check;
	char buf[20];
	fgets(buf,45,stdin);
	
	if (check==0xdeadbeef)
	{
		setreuid(3095,3095);
		system("/bin/sh");
	}
	
	printf(" Input is : %s\n &buf : %p\n &check:%p\n &crap :%p\n", buf, buf, &check,&crap);
}
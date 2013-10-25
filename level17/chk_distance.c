#include <stdio.h>

void printit( ) {
	printf("Hello there!\n");
}

main( )
{
	int crap;
	void (*call)( )=printit;
	char buf[20];
	fgets(buf,48,stdin);
	setreuid(3098,3098);
	call( );
	printf(" Input is : %s\n &buf : %p\n &call:%p\n &crap :%p\n", buf, buf, &call,&crap);
}
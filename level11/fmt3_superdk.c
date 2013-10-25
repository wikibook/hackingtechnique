#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{
	static int i=0;
	char str[128];

	strcpy( str, argv[1] );
	printf( str );
	printf( "\ni=%p, i=%d\n", &i, i);
}
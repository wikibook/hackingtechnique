/*
 * Author : superdk@hanmail.net
 * DATA : exploit for level7
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <string.h>

#define MAXARRAY 4

int binToInt(char *bin);

int main()
{
        int i, decimal[MAXARRAY];

        char *bin = "--_--_- --____- ---_-__ --__-_-";

	char *ptr = bin;
        char dec[MAXARRAY*8];
	char ascii[MAXARRAY];


	printf("Resvered signals : --_--_- --____- ---_-__ --__-_-\n");
	
	for(i=0; i<strlen(bin); i++)
	{
		if( *ptr == '-' )
			dec[i] = '1';
		else if( *ptr == '_' )
			dec[i] = '0';
		else if( *ptr == ' ' )
			dec[i] = '\0';
		ptr++;
	}
	
	dec[i] = '\0';

	printf("Changed binary : %s %s %s %s\n", &dec[0], &dec[8], &dec[16], &dec[24]);
	
	
	
	printf("Changed decimal :");
	for(i=0; i<MAXARRAY; i++)
	{
		decimal[i] = binToInt(&dec[i*8]);
		printf( " %d ", decimal[i] );
	}
	printf("\n");
	
	printf("Changed ascii :");
	for(i=0; i<MAXARRAY; i++)
	{
		printf( " %c ", decimal[i] );
	}
	printf( "\n" );
}


int binToInt(char *bin) {
  int i = 0;
  int count = 0;

  while (bin[count])
    i = (i << 1) | (bin[count++] - '0');

  return i;
}

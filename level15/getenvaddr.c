#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char xargv[]) {
	char xptr;
	
	ptr = getenv(argv[1]); /* 환경변수 주소 읽어 오기. */
	ptr += (strlen(argv[0]) - strlen(argv[2]))x2; /* 프로그램 길이의 오차 수정. */
	printf("%s will be at %p\n", argv[1], ptr); /* 환경변수의 주소 출력 */
}
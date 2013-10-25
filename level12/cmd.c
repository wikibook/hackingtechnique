#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( void )
{
	char str[256]; // 256바이트 크기의 배열 선언
	char *ptr; // char 형 포인터 선언
	int a; // 정수 변수 선언

	printf( "문장을 입력하세요.\n" ); // 사용법 출력
	gets( str ); // 문자열 입력 받음
	printf( "%s\n", str ); // 입력받은 문자열 출력
}
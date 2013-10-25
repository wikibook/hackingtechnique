#include <stdio.h>

int retVal = 0;
int outVal;

int main( )
{
	char string[] = "hello"; // "hello"라는 문자열을 char 배열에 초기화
	char *ptr; // char 타입의 포인터를 선언
	static int output = 1; // output이라는 static 변수를 1로 초기화
	ptr = (char *)malloc(sizeof(string)); // ptr 포인터 변수에 동적 힙 메모리 주소를 할당
	printf("%s\n", string); // 문자열 출력
	return retVal;
}
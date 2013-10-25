/*
 * Author : superdk@hanmail.net
 * DATA : pseudo for level7
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <malloc.h>

int main( )
{
	char *input;
	char *pass = "mate";

	if( (input = (char *)malloc(0x64)) == NULL )
	{
		printf("malloc( ) error\n");
		exit(1);
	}
	printf("Insert The Password : ");
	
	fgets(input, 0x64, stdin);
	
	if(strncmp(input, pass, 0x4) == 0) // 입력받은 문자열의 앞자리 4자만 체크한다
	{
		printf("\nCongratulation! next password is \"break the world\".\n\n");
		exit(0);
	}
	else
		system("cat /bin/wrong.txt");
	
	free(input); // 디버깅에서는 없었지만 습관적으로 해제해 주는 것이 좋다
	return 0;
}
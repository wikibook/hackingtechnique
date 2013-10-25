/*
 * Author : superdk@hanmail.net
 * DATA : pseudo code for level1
 * LICENSE : GNU License
 */
 
 
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char input[29];
    char *denyMyPass = "my-pass";
    char *denyChmod = "chmod";
    
    system("clear");
    chdir("/home/level2");
    printf("\n\n\n\t\t레벨2의 권한으로 당신이 원하는 명령어를\n");
    printf("\t\t한가지 실행시켜 드리겠습니다.\n");
    printf("\t\t(단, my-pass 와 chmod는 제외)\n");
    printf("\n\t\t어떤 명령을 실행시키겠습니까?\n");
    printf("\n\n\t\t[level2@ftz level2]$ ");
    
    fgets(input, sizeof(input), stdin);
    
    if( strstr(input, denyMyPass) != NULL )
    {
        printf("\n\t\tmy-pass 명령은 사용할 수 없습니다.\n\n");
        exit(0);
    }
    else if( strstr(input, denyChmod) != NULL )
    {
        printf("\n\t\tchmod 명령은 사용할 수 없습니다.\n\n");
        exit(0);
    }
    printf("\n\n");
    
    setreuid(3002, 3002);
    system(input);
}
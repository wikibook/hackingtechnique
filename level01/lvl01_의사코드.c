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
    printf("\n\n\n\t\t����2�� �������� ����� ���ϴ� ��ɾ\n");
    printf("\t\t�Ѱ��� ������� �帮�ڽ��ϴ�.\n");
    printf("\t\t(��, my-pass �� chmod�� ����)\n");
    printf("\n\t\t� ����� �����Ű�ڽ��ϱ�?\n");
    printf("\n\n\t\t[level2@ftz level2]$ ");
    
    fgets(input, sizeof(input), stdin);
    
    if( strstr(input, denyMyPass) != NULL )
    {
        printf("\n\t\tmy-pass ����� ����� �� �����ϴ�.\n\n");
        exit(0);
    }
    else if( strstr(input, denyChmod) != NULL )
    {
        printf("\n\t\tchmod ����� ����� �� �����ϴ�.\n\n");
        exit(0);
    }
    printf("\n\n");
    
    setreuid(3002, 3002);
    system(input);
}
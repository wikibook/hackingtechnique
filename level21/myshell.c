#include<stdio.h>

int main( )
{
	char *bash[] = {"/bin/sh", 0};
	execve(bash[0], &bash, 0);
}
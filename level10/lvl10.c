/*
 * Author : superdk@hanmail.net
 * DATA : example for level10
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
	char buf[BUFFSIZE]="3456";
	key_t keyval = 7777;
	
	/*공유 메모리를 생성하고, 해당 메모리에 값을 쓴다 */
	sharedMemID = shmget(keyval, BUFFSIZE, IPC_CREAT | 0666);
	
	/*프로세스에서 공유 메모리 공간을 사용할 수 있게 연결(Attach)한다 */
	sharedMemory = shmat(sharedMemID, (void *)0, 0);
	
	/*공유 메모리 공간에 있는 값을 특정 변수에 복사한다 */
	memcpy(sharedMemory, buf, BUFFSIZE);
	printf("%s\n", sharedMemory);
	
	/*프로세스에서 공유 메모리의 연결을 분리(Detach)한다 */
	shmdt(sharedMemory);
	
	return 0;
}
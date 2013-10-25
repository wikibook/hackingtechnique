#include<stdio.h>
#include<signal.h>
#include<unistd.h>

// SIGINT(Ctrl+C) 시그널이 입력됐을 때 실행되는 함수
void sigint_handler(int signo)
{
	printf("received %d\n", signo);
	signal(SIGINT, SIG_DFL); // SIGINT 시그널을 실행한다.
}

// SIGTSTP(Ctrl+Z) 시그널이 입력됐을 때 실행되는 함수
void sigtstp_handler(int signo)
{
	printf("received %d\n", signo);
	signal(SIGTSTP, SIG_IGN); // SIGTSTP 시그널을 실행하지 않는다.
}

// SIGQUIT(Ctrl+\) 시그널이 입력됐을 때 실행되는 함수
void sigquit_handler(int signo)
{
	printf("received %d\n", signo);
	signal(SIGQUIT, SIG_DFL); // SIGQUIT 시그널을 실행한다.
}


int main(void)
{
	// SIGINT(Ctrl+C) 시그널이 입력됐을 때 sigint_handler( )를 실행한다
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		printf("\ncan't catch signal\n");
	
	// SIGTSTP(Ctrl+Z) 시그널이 입력됐을 때 sigtstp_handler( )를 실행한다
	if (signal(SIGTSTP, sigtstp_handler) == SIG_ERR)
		printf("\ncan't catch signal\n");
	
	// SIGQUIT(Ctrl+\) 시그널이 입력됐을 때 sigquit_handler( )를 실행한다
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
		printf("\ncan't catch signal\n");
	// 시그널로 입력되는 키를 확인하기 위해 무한히 실행한다.
	while(1)
		sleep(1);
	
	return 0;
}
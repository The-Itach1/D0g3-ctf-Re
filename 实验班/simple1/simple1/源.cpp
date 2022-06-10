#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)

unsigned char enc[33] = { 0x65,0x50,0x8a,0x57,0x98,0x53,0x83,0x52,0x5a,0x5c,0x5b,0x58,0x8e,0x8e,0x8a,0x5a,0x93,0x42,0x90,0x4b,0x43,0x96,0x4c,0x4f,0x4a,0x43,0x9f,0x41,0x4e,0x4f,0x4f,0x81 };

BOOL checkflag(unsigned char* flag)
{
	if (memcmp(flag, enc, 32) == 0)
	{
		return 1;
	}
	return 0;
}

//"D0g3{5d41402abc4b2a76b9719d9110}"
int main()
{
	unsigned char flag[33];
	int i;

	printf("please inupt the flag:");
	scanf("%s", flag);

	for (i = 0; i < 32; i++)
	{
		flag[i] = (flag[i] + 33) ^ i;
	}

	if (checkflag(flag) != 0)
	{
		printf("\nsuccess!");
	}
	else
	{
		printf("\nfailed!");
	}
}
#include<stdio.h>
#include "string.h"

int main(void) 
{
	char a[]="!y1gu_0s_si_g4lf";
	int i,t; 
	int len=strlen(a);
	
	for(i = 0; i < len/2; i++)
	{
		t = a[i];
		a[i] = a[len-i-1];
		a[len-i-1] = t;
	}
	
	printf("%d",len);
	printf("\n");
	for(i=0;a[i]!='\0';i++)
	{
		printf("%c",a[i]);
	}
}

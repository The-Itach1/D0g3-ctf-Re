#include<stdio.h>

int main()
{
	int a[]={0x6b,0x65,0x60,0x66,0x68,0x35,0x61,0x35,0x6e,0x30,0x61,0x31,0x39,0x60,0x3d,0x63,0x35,0x65,0x66,0x32,0x6c,0x30,0x63,0x30,0x6b,0x60,0x60,0x30,0x6b,0x33,0x3d,0x60};
  	int i,j;
	printf("0x");
	for(i=0;i<100*4;i+=4)
	{
		for(j=i+3;j>=i;j--)
		{
			printf("%02x",a[j]);
		}
		printf(",0x") ;
	}
	
}

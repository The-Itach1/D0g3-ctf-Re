#include<stdio.h>
#include<string.h>

int main(void)
{
	char s[100]="7967736E616D7577";
	int i,j;
	int a[100];
	 
	for(i=0;i<50;i++)
	{
		
		if(s[i]>=48&&s[i]<=57)
		s[i]=s[i]-48;
		else if(s[i]>=97&&s[i]<=102)
		s[i]=s[i]-87;
		else if(s[i]>=65&&s[i]<=70)
		s[i]=s[i]-55;
		
	}
	
	for(i=0,j=1;i<50;i=i+2,j=j+2)
	{
		a[0]=s[i]*16+s[j];
		printf("%c,",a[0]);
	}
	
//	for(i=0;i<6;i++)
//	{
//		for(j=0;j<8;j++)
//		{
//			ch=code[i]&0xff;
//			printf("%c",ch);
//			code[i]=code[i]>>8;			
//		}
//
//	}
}

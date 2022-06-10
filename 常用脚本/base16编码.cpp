#include<stdio.h>
#include<string.h>

int main(void)
{
	char date[100]="bacde";
	char code[100];
	unsigned char table[17]="0123456789ABCDEF";
	int len_date,len_code,i,j,num;
	
	len_date=strlen(date);
	printf("明文长度为len_date=%d\n",len_date);
	printf("明文为：%s\n",date);
	len_code=len_date*2;
	
	for(i=0,j=0;i<len_date;i++,j+=2)
	{
		code[j]=table[date[i]>>4];
		code[j+1]=table[date[i]&15]; 
	}
	
	printf("密文长度len_code=%d\n",len_code);
	printf("密文为："); 
	for(i=0;i<len_code;i++)
	{
		printf("%c",code[i]);
	}
} 

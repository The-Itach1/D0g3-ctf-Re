#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[])
{
	char date[100]="bacde";
	char code[100];
	unsigned char table[33]="ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
	int len_date,len_code,i,j,num;
	
	len_date=strlen(date);
	printf("明文长度为len_date=%d\n",len_date);
	printf("明文为：%s\n",date);
	if(len_date%5!=0)
	{
		len_code=(len_date/5+1)*8;
	}
	else
	{
		len_code=(len_date/5)*8; 
	}
	
	for(i=0,j=0;i<len_code;i+=5,j+=8)
	{
		code[j]=table[date[i]>>3];
		code[j+1]=table[((date[i]&7)<<2)|(date[i+1]>>6)];
		code[j+2]=table[(date[i+1]>>1)&31];
		code[j+3]=table[(date[i+1]&1)<<4|date[i+2]>>4];
		code[j+4]=table[(date[i+2]&15)<<1|date[i+3]>>7];
		code[j+5]=table[(date[i+3]>>2)&31];
		code[j+6]=table[(date[i+3]&3)<<3|date[i+4]>>5];
		code[j+7]=table[date[i+4]&31];
	}
	num=len_date%5;
	switch(num)
	{
		case 1: 
			for(i=1;i<8-num;i++)
			{
				code[len_code-i]='=';
			}
			break;
			
		case 2:
			for(i=1;i<7-num;i++)
			{
				code[len_code-i]='=';
			}		
			break;
			
		case 3:
			for(i=1;i<7-num;i++)
			{
				code[len_code-i]='=';
			}		
			break;
		case 4:
			code[len_code-1]='=';	
			break;
	}
	printf("密文长度len_code=%d\n",len_code);
	printf("密文为："); 
	for(i=0;i<len_code;i++)
	{
		printf("%c",code[i]);
	}	
}

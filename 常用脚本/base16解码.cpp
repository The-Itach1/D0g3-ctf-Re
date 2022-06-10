#include<stdio.h>
#include<string.h>

int main(void)
{
	char code[100]="6261636465";
	char date[100];
	int table[]={0,0,0,0,0,0,0,0,0,0,0,0,
	    		 0,0,0,0,0,0,0,0,0,0,0,0,
	    		 0,0,0,0,0,0,0,0,0,0,0,0,
	    		 0,0,0,0,0,0,0,62,0,0,0,
	    		 63,0,1,2,3,4,5,6,
	    		 7,8,9,0,0,0,0,0,0,0,10,
	    		 11,12,13,14,15
	    	   };
//	    	   printf("%d",table['A']); 
	int len_date,len_code,i,j,num;
	
	len_code=strlen(code);
	printf("密文长度为len_code=%d\n",len_code);
	printf("密文为：%s\n",code);
	len_date=len_code/2;
	
	for(i=0,j=0;i<len_code;i+=2,j++)
	{
		date[j]=table[code[i]]<<4|table[code[i+1]];
	}
	
	printf("明文长度为len_date=%d\n",len_date); 
	printf("明文为：");
	for(i=0;i<len_date;i++)
	{
		printf("%c",date[i]);
	 } 
	
} 

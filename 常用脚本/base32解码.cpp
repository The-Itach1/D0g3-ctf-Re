#include<stdio.h>
#include<string.h>

int main(void)
{
	char code[100]="MJQXG3LTMZZWCZQ=";
	char date[100];
	int table[]={0,0,0,0,0,0,0,0,0,0,0,0,
	    		 0,0,0,0,0,0,0,0,0,0,0,0,
	    		 0,0,0,0,0,0,0,0,0,0,0,0,
	    		 0,0,0,0,0,0,0,0,0,0,0,
	    		 0,0,0,26,27,28,29,30,
	    		 31,0,0,0,0,0,0,0,0,0,0,
	    		 1,2,3,4,5,6,7,8,9,10,11,12,
	    		 13,14,15,16,17,18,19,20,21,
	    		 22,23,24,25
	    	   };
 
	int len_date,len_code,i,j,num;
	
	len_code=strlen(code);
	printf("密文长度为len_code=%d\n",len_code);
	printf("密文为：%s\n",code);
	if(strstr(code,"======"))
	{
		len_date=(len_code/8)*5-4;
	}	
	else if(strstr(code,"===="))
	{
		len_date=(len_code/8)*5-3;
	}
	else if(strstr(code,"==="))
	{
		len_date=(len_code/8)*5-2;
	}
	else if(strstr(code,"="))
	{
		len_date=(len_code/8)*5-1;
	}
	else
	{
		len_date=(len_code/8)*5;
	}		
	for(i=0,j=0;j<len_date;i+=8,j+=5)
	{
		date[j]=table[code[i]]<<3|table[code[i+1]]>>2;
		date[j+1]=table[code[i+1]]<<6|table[code[i+2]]<<1|table[code[i+3]]>>4;
		date[j+2]=table[code[i+3]]<<4|table[code[i+4]]>>1;
		date[j+3]=table[code[i+4]]<<7|table[code[i+5]]<<2|table[code[i+6]]>>3;
		date[j+4]=table[code[i+6]]<<5|table[code[i+7]];
	}
	
	printf("明文长度为len_date=%d\n",len_date); 
	printf("明文为：");
	for(i=0;i<len_date;i++)
	{
		printf("%c",date[i]);
	}
	
} 

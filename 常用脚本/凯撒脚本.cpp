#include<stdlib.h>
#include<string.h>
#include<stdio.h>
int main(void)
{
	char table1[27]="abcdefghijklmnopqrstuvwxyz";
	char table2[27]="ABCDEFJHIJKLMNOPQRSTUVWXYZ";
	char str1[100]="qypth{hp5d_s0n_szi^3ic&qh11a_}";
	char str2[100]="";
	int i,k,len;
	
	len=strlen(str1);
	for(k=0;k<26;k++)
	{
		for(i=0;i<len;i++)
		{
			if(str1[i]>=table1[k]&&str1[i]<='z')
			{
				str2[i]=str1[i]-k;
			}
			else if(str1[i]<table1[k]&&str1[i]>='a')
			{
				str2[i]=str1[i]+26-k;
			}
			else if(str1[i]>=table2[k]&&str1[i]<='Z')
			{
				str2[i]=str1[i]-k;
			}
			else if(str1[i]<table2[k]&&str1[i]>='A')
			{
				str2[i]=str1[i]+26-k;
			}			
			else
			{
				str2[i]=str1[i];
			}
		}
		printf("%s",str2);
		printf("\n");
	}
 } 

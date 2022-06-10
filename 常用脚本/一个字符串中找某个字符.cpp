#include<stdio.h>
#include<windows.h>

int main(void)
{
	int a[33]={'2', '1', '6', '3', 'q', 'w', 'e', ')', '(', '*', '&', '^', '%', '4', '8', '9', '$', '!', '0', '5', '7', '@', '#', '>', '<', 'A'};
	int v4[7]={65,101,48,53,57,33,49};
	int i,j;
	
	for(i=0;i<7;i++)
	{
		for(j=0;j<=32;j++)
		{
			if(v4[i]==a[j])
			{
				printf("%d ",j);
				break;
			}
		}
	}
}

#include<stdio.h>
#include<string.h>
#define IDEA_ADD_MODULAR    65536

#define IDEA_MP_MODULAR     65537
unsigned short endkey[52];

void swap(unsigned short *a,unsigned short *b)
{
	unsigned short c;
	c=*a;
	*a=*b;
	*b=c;
}
unsigned short add_mod(unsigned short a,unsigned short b)
{
	unsigned short tmp=a+b;
	return tmp%IDEA_ADD_MODULAR;
}

unsigned short mp_mod(unsigned short a,unsigned short b)
{
	unsigned long long tmp, tmp_a, tmp_b;
	tmp_a = a == 0 ? (1 << 16) : a;
	tmp_b = b == 0 ? (1 << 16) : b;
	tmp = (tmp_a * tmp_b) % IDEA_MP_MODULAR;
	return (unsigned short)(tmp);
}
void releft(unsigned short temkey[])
{
	unsigned high=temkey[0]>>(16-5);
	int i;
	for(i=0;i<7;i++)
	{
		temkey[i]=(temkey[i]<<5)|(temkey[i+1]>>(16-5));
	}
	temkey[7]=temkey[7]<<5|high;
}

void extendkey(unsigned char key[])
{
	int i,j,k;
	unsigned short temkey[8];
	
	//得到开始的8个endkey 
	for(i=0;i<8;i++)
	{
		temkey[i]=(key[i*2]<<8)|(key[i*2+1]);
		endkey[i]=(key[i*2]<<8)|(key[i*2+1]);
	//	printf("%04x ",endkey[i]);
	}
	
	//用暂时保存的temkey来扩展
	for(i=1;i<=5;i++)
	{
		for(j=0;j<5;j++)
		{
			releft(temkey);
		}
		for(k=0;k<8;k++)
		{
			endkey[i*8+k]=temkey[k];
		}
	} 
	//最后4个密钥 
	for(j=0;j<5;j++)
	{
		releft(temkey);
	}
	
	for(i=0;i<4;i++)
	{
		endkey[48+i]=temkey[i];
	}
}

void idea_round(unsigned short X[],int group)
{
	unsigned short out[4],tmp[4],mid[4],mid_out[2];
	int i;
	tmp[0]=mp_mod(X[0],endkey[6*group+0]);//1
	tmp[1]=add_mod(X[1],endkey[6*group+1]);//2
	tmp[2]=add_mod(X[2],endkey[6*group+2]);//3
	tmp[3]=mp_mod(X[3],endkey[6*group+3]);//4

	mid[0]=tmp[0]^tmp[2];//5
	mid[1]=tmp[1]^tmp[3];//6
	
	mid[2]=mp_mod(mid[0],endkey[6*group+4]);//7
	mid[3]=add_mod(mid[1],mid[2]);//8


	mid_out[0]=mp_mod(mid[3],endkey[6*group+5]);//9
	mid_out[1]=add_mod(mid[2],mid_out[0]);//10

	out[0]=tmp[0]^mid_out[0];
	out[1]=tmp[1]^mid_out[1];
	out[2]=tmp[2]^mid_out[0];
	out[3]=tmp[3]^mid_out[1];
	swap(&out[1],&out[2]);
	
	for(i=0;i<4;i++)
	{
		X[i]=out[i];
		printf("%04x ",X[i]);
	}
	
}

void encrypt(unsigned char key[],unsigned char date[],unsigned short out[])
{
	int i,j,rounds,count;
	unsigned char *key1;
	unsigned char *date1;
	unsigned short X[4];
	
	key1=key;
	date1=date;

	extendkey(key1);
	
	for(i=0;i<52;i++)
	{
	//	printf("%04x ",endkey[i]);
	}
	
	
	rounds=strlen((const char*)date)/8;
	for(count=0;count<rounds;count++)
	{
		for(i=0;i<4;i++)
		{
			X[i]=(date1[i*2]<<8)|(date1[i*2+1]);
		} 
	
	
		for(i=0;i<8;i++)
		{
			idea_round(X,i);
			printf("\n");
		}
		//最后一轮
		swap(&X[1],&X[2]);
		X[0]=mp_mod(X[0],endkey[48]);
		X[1]=add_mod(X[1],endkey[49]);
		X[2]=add_mod(X[2],endkey[50]);
		X[3]=mp_mod(X[3],endkey[51]);
		
		for(i=0;i<4;i++)
		{
			out[i+count*4]=X[i];
		}
	}
}

int main()
{
	unsigned char key[]="1234567812345678";
	unsigned char date[]="1234567812345678";
	unsigned short out[8];
	unsigned char buffer[256];
	int i;
	
	encrypt(key,date,out);
	printf("\n");
//	for(i=0;i<8;i++)
//	{
//		printf("%02x %02x ",*((char*)&out[i])&0xff,*((char*)&out[i] + 1)&0xff);
//	}
//	printf("\n");
	for(i=0;i<8;i++)
	{
		printf("%04x ",out[i]);
	}
}

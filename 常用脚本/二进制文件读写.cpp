#include<stdio.h>
#include<math.h>
 int main(void){
	
   	FILE *p;
    char v[0x5FE0]={0};
    int i;

    p=fopen("abc.bin","rb");
    fread(&v, 1, 0x5FE0, p);
    for(i=0;i<0x5FE0;i++)
    {
        v[i]=v[i]^65;
    }
    FILE *p1 = fopen("def.bin", "wb");
    fwrite(&v, 1, 0x5FE0, p1);
} 

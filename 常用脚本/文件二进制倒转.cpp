#include<stdio.h>

int main()
{
    unsigned char v[0x12667]={0};
    unsigned char v2[0x12667]={0};
    int i;
    FILE *p1 = fopen("./happy", "rb");
    fread(&v, 1, 0x12667, p1);
    fclose(p1);
    for(i=0;i<0x12667;i++)
    {
        v2[i]=v[0x12666-i];
        printf("%02x ",v2[i]);
    }
    
    FILE *p2 = fopen("./happy1", "wb");
    fwrite(&v2, 1, 0x12667, p2);
    fclose(p2);
    return 0;
}

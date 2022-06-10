#include<stdio.h>

void xxteadecrypt(unsigned int* code, unsigned int* key, unsigned int n)
{
    unsigned int next, end, sum;
    unsigned int rounds, e, delta = 0x9e3779b9;
    int i;

    rounds = 6 + 52 / n;
    sum = rounds * delta;
    next = code[0];//设置next为code的第一个 
    do
    {
        e = (sum >> 2) & 3;
        for (i = n - 1; i > 0; i--)//解密最后一个到第二个
        {
            end = code[i - 1];
            code[i] -= (((end >> 5 ^ next << 2) + (next >> 3 ^ end << 4)) ^ ((sum ^ next) + (key[(i & 3) ^ e] ^ end)));
            next = code[i];
        }
        end = code[n - 1];
        code[0] -= (((end >> 5 ^ next << 2) + (next >> 3 ^ end << 4)) ^ ((sum ^ next) + (key[i & 3 ^ e] ^ end)));
        next = code[0];
        sum -= delta;
    } while (--rounds);

}



int main()
{
    unsigned int key[4] = { 'D','0','g','3' };
    unsigned int n = 8;
    unsigned int code[9] = {  0xD04F9B3F, 0x14E3D512, 0xDB62246E, 0x1290C9C0, 0x7417372C, 0x48478F9C, 0xE58A627D, 0xD2659A75 };
    unsigned int flag[19]={61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61};
    unsigned int i;
    
	for(i=0;i<18;i++)
	{
		//printf("%08x ",flag[i]);
	 } 
	xxteadecrypt(code, key, n);
    

	for(i=0;i<8;i++)
    {
        printf("%c%c%c%c",*((char*)&code[i]+3),*((char*)&code[i]+2),*((char*)&code[i]+1),*((char*)&code[i]+0));
    }


}


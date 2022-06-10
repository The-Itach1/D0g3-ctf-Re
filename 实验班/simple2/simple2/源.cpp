#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
unsigned char enc[45] = "PJVqalzl1o1e+Jct6Hct+5MM1vAsa4aScvVM1iYMame=";


int checkflag(unsigned char* flag, int len)
{
    if (memcmp(flag, enc, len) == 0)
    {
        return 1;
    }
    return 0;
}

int base64encrypt(char* str1, unsigned char** retstr2, int* retlen)
{
    unsigned char* str2;
    int len1;
    int len2;
    int i, j;
    const char* table = "QVEJAfHmUYjBac+u8Ph5n9Od16FrICL/X0GvtM4qk7T2z3wNSsyoebilxWKgZpRD";

    len1 = strlen(str1);

    if (len1 % 3 != 0)
    {
        len2 = (len1 / 3 + 1) * 4;
    }
    else
    {
        len2 = (len1 / 3) * 4;
    }

    str2 = (unsigned char*)malloc(sizeof(unsigned char) * len2 + 1);
    str2[len2] = '\0';

    __asm {
            xor eax, eax
            test eax, eax
            je LABEL1
            jne LABEL2
        LABEL2 :
            _emit 0x5e
            and eax, ebx
            _emit 0x50
            xor eax, ebx
            _emit 0x74
            add eax, edx
        LABEL1 :
    }
    for (i = 0, j = 0; i < len1; i += 3, j += 4)
    {
        str2[j] = table[str1[i] >> 2];
        str2[j + 1] = table[(((str1[i] & 3) << 4) | (str1[i + 1] >> 4))];
        str2[j + 2] = table[((str1[i + 1] & 15) << 2) | (str1[i + 2] >> 6)];
        str2[j + 3] = table[str1[i + 2] & 0x3f];
    }

    switch (len1 % 3)
    {
    case 1:
        str2[len2 - 2] = '=';
        str2[len2 - 1] = '=';
        break;
    case 2:
        str2[len2 - 1] = '=';
        break;
    }

    *retstr2 = str2;
    *retlen = len2;
    return 0;
}


//"D0g3{7c6483ddcd99eb112c060ecbe0}"
int main(int argc, char* argv[]) {

    char flag[33];

    printf("please input the flag:");
    scanf("%s", flag);
    unsigned char* enc = NULL;
    int enclen;
    base64encrypt(flag, &enc, &enclen);
    //printf("%s", enc);
    if (checkflag(enc, enclen) != 0)
    {
        printf("\nsuccess!");
    }
    else
    {
        printf("\nfailed!");
    }

    if (enc != NULL)
    {
        free(enc);
    }

    return 0;
}
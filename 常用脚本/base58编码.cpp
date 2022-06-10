#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
    char date[] = "AB";
    int i,index = 0;
    long long sum = 0;
    int len_date=strlen(date);
    int len_code=strlen(date) *138/100;// len * log(2)256 / log(2)(58)
    int len=len_code + 1;//加1是因为用动态数组时结尾那个'\0' 
    char base58Table[59] = "123456789abcdefghijkmnopqrstuvwxyzABCDEFGHJKLMNPQRSTUVWXYZ";
	char *code = (char *)malloc(len * sizeof(char));

    memset(code,0,len * sizeof(char));
	len_date=strlen(date);
	printf("明文长度为len_date=%d\n",len_date);
	printf("明文为：%s\n",date);
    //方法一，基本上不可用，明文长一点就没办法了。 
//    for(i = 0; i < strlen(plainText); i++) {//可以首先获取累加和 但是这样做的风险就是 随着幂的增加 和会急速暴增
//        sum += plainText[i] * pow(256,strlen(plainText)-i-1);
//    }
//
//    cout << sum << endl;
//    for(i = len - 1; i >= 0; i--) {
//        encryption[i] = base58Table[sum % 58];
//        sum /= 58;
//        if(0 == sum )
//            break;
//    }


    //方法二 每次都模 这样就不会存在和超出最大范围
    while(index < len_date ) //这个while循环实现的是数制转换 
	{
        int each = date[index];
        for(i = len_code;1;i--)
		{
            each = each + code[i] * 256;
            code[i] = each % 58;
            each /= 58;
            if(each==0)
                break;
        }

        i = 0;//输出
        while(!code[i])
            i++;
        printf("第%d轮code[]数组的值",index+1); 
        for(;i <= len_code; i++) 
		{
            printf("%-3d ",code[i]);
        }
        printf("\n") ;
        index++;
    }

    i = 0;
    while(!code[i])
        i++;
	printf("密文长度len_code=%d\n",len_code);
	printf("密文为：");     
    for(;i <= len_code; i++) 
	{
        printf("%c",base58Table[code[i]]);
    }
    return 0;
}



//A:65  B:66
//第一轮求58的模:       第二轮求58的模： 
//65%58=7				  (7*256+66)%58=2
//65/58=1				  (7*256+66)/58=32
//1%58=1				  (1*256+32)%=56
//1/58=1				  (1*256+32)/58=4
//					  (0*256+4)%58=4
//					  (4/58)=0

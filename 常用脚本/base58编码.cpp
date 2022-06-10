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
    int len=len_code + 1;//��1����Ϊ�ö�̬����ʱ��β�Ǹ�'\0' 
    char base58Table[59] = "123456789abcdefghijkmnopqrstuvwxyzABCDEFGHJKLMNPQRSTUVWXYZ";
	char *code = (char *)malloc(len * sizeof(char));

    memset(code,0,len * sizeof(char));
	len_date=strlen(date);
	printf("���ĳ���Ϊlen_date=%d\n",len_date);
	printf("����Ϊ��%s\n",date);
    //����һ�������ϲ����ã����ĳ�һ���û�취�ˡ� 
//    for(i = 0; i < strlen(plainText); i++) {//�������Ȼ�ȡ�ۼӺ� �����������ķ��վ��� �����ݵ����� �ͻἱ�ٱ���
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


    //������ ÿ�ζ�ģ �����Ͳ�����ںͳ������Χ
    while(index < len_date ) //���whileѭ��ʵ�ֵ�������ת�� 
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

        i = 0;//���
        while(!code[i])
            i++;
        printf("��%d��code[]�����ֵ",index+1); 
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
	printf("���ĳ���len_code=%d\n",len_code);
	printf("����Ϊ��");     
    for(;i <= len_code; i++) 
	{
        printf("%c",base58Table[code[i]]);
    }
    return 0;
}



//A:65  B:66
//��һ����58��ģ:       �ڶ�����58��ģ�� 
//65%58=7				  (7*256+66)%58=2
//65/58=1				  (7*256+66)/58=32
//1%58=1				  (1*256+32)%=56
//1/58=1				  (1*256+32)/58=4
//					  (0*256+4)%58=4
//					  (4/58)=0

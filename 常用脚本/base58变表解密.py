import base58

code='yVWN4863jhhiKDftAgnMH=el2my-0c1{0'

table1='987GHJKLMPQRSUVWX6432*BCDFlag{n0T-EA5y=to+f1Nd}YZbcehijkmp'
table2='123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz'
code2=''
flag=''
for i in range(len(code)):
    for j in range(len(table1)):
        if code[i]==table1[j]:
            code2+=table2[j]
            break
#print(code2)
flag=base58.b58decode(code2)
print(len(flag))
print(flag)
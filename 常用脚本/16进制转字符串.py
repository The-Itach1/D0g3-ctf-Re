code=[7378644943136451686,7148951143638579506,3257850080642543666,
      3835203404393046370,7363777037631763767,32056]
flag=[0]*6
def print_flag(s):
    str=''
    for i in range(0,len(s),2):
        a=int(s[i:i+2],16)
        str+=chr(a)
    print(str[::-1],end='')

for i in range(6):
    flag[i]=(hex(code[i]).replace('0x',''))
    print_flag(flag[i])
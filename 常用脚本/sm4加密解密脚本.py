SBOX = ['d6', '90', 'e9', 'fe', 'cc', 'e1', '3d', 'b7', '16', 'b6', '14', 'c2', '28', 'fb', '2c', '05',
       '2b', '67', '9a', '76', '2a', 'be', '04', 'c3', 'aa', '44', '13', '26', '49', '86', '06', '99',
       '9c', '42', '50', 'f4', '91', 'ef', '98', '7a', '33', '54', '0b', '43', 'ed', 'cf', 'ac', '62',
       'e4', 'b3', '1c', 'a9', 'c9', '08', 'e8', '95', '80', 'df', '94', 'fa', '75', '8f', '3f', 'a6',
       '47', '07', 'a7', 'fc', 'f3', '73', '17', 'ba', '83', '59', '3c', '19', 'e6', '85', '4f', 'a8',
       '68', '6b', '81', 'b2', '71', '64', 'da', '8b', 'f8', 'eb', '0f', '4b', '70', '56', '9d', '35',
       '1e', '24', '0e', '5e', '63', '58', 'd1', 'a2', '25', '22', '7c', '3b', '01', '21', '78', '87',
       'd4', '00', '46', '57', '9f', 'd3', '27', '52', '4c', '36', '02', 'e7', 'a0', 'c4', 'c8', '9e',
       'ea', 'bf', '8a', 'd2', '40', 'c7', '38', 'b5', 'a3', 'f7', 'f2', 'ce', 'f9', '61', '15', 'a1',
       'e0', 'ae', '5d', 'a4', '9b', '34', '1a', '55', 'ad', '93', '32', '30', 'f5', '8c', 'b1', 'e3',
       '1d', 'f6', 'e2', '2e', '82', '66', 'ca', '60', 'c0', '29', '23', 'ab', '0d', '53', '4e', '6f',
       'd5', 'db', '37', '45', 'de', 'fd', '8e', '2f', '03', 'ff', '6a', '72', '6d', '6c', '5b', '51',
       '8d', '1b', 'af', '92', 'bb', 'dd', 'bc', '7f', '11', 'd9', '5c', '41', '1f', '10', '5a', 'd8',
       '0a', 'c1', '31', '88', 'a5', 'cd', '7b', 'bd', '2d', '74', 'd0', '12', 'b8', 'e5', 'b4', 'b0',
       '89', '69', '97', '4a', '0c', '96', '77', '7e', '65', 'b9', 'f1', '09', 'c5', '6e', 'c6', '84',
       '18', 'f0', '7d', 'ec', '3a', 'dc', '4d', '20', '79', 'ee', '5f', '3e', 'd7', 'cb', '39', '48',]
FK = ['a3b1bac6', '56aa3350', '677d9197', 'b27022dc']
CK = ['00070e15', '1c232a31', '383f464d', '545b6269',
      '70777e85', '8c939aa1', 'a8afb6bd', 'c4cbd2d9',
      'e0e7eef5', 'fc030a11', '181f262d', '343b4249',
      '50575e65', '6c737a81', '888f969d', 'a4abb2b9',
      'c0c7ced5', 'dce3eaf1', 'f8ff060d', '141b2229',
      '30373e45', '4c535a61', '686f767d', '848b9299',
      'a0a7aeb5', 'bcc3cad1', 'd8dfe6ed', 'f4fb0209',
      '10171e25', '2c333a41', '484f565d', '646b7279']
def left(list,n):
    return list[n:] + list[:n]
def group(list, n):
    for i in range(0, len(list), n):
        yield list[i:i + n]
def xor(a,b):
    a1 = int(a,16)
    b1 = int(b,16)
    if a == b:
        A = '{:032x}'.format(int(a1^b1))
    else:
        A = '{:08x}'.format(int(a1^b1))
    return A
def round_function(k0,k1,k2,k3,rk,mod):
    k = xor(xor(xor(k1,k2),k3),rk)
    Tr = T(k,mod)
    rki = xor(k0,Tr)
    return rki
def T(A,mod):
    T = linear(S(A),mod)
    return T
def S(A):
    A1 = []
    A2 = [0,0,0,0]
    for i in group(A,2):
        A1.append(i)
    for i in range(4):
        l = int(A1[i],16)
        A2[i] = '{:02x}'.format(int(SBOX[l],16))
    A2 = ''.join(A2)
    return A2
def linear(B,mod):
    B1 = list(B)
    for i in range(8):
        B1[i] = '{:04b}'.format(int(B1[i],16))
    B1 = ''.join(B1)
    B1_2= left(B1,2)
    B1_10 = left(B1,10)
    B1_18 = left(B1,18)
    B1_24 = left(B1,24)
    B1_13 = left(B1,13)
    B1_23 = left(B1,23)
    if mod == 'enc' or mod ==  'dec':
        BX = xor(xor(xor(xor(B1,B1_2),B1_10),B1_18),B1_24)
    elif mod == 'extend':
        BX = xor(xor(B1,B1_13),B1_23)
    else:
        return "模式输入错误"
    BX = '%x'%int(BX, 2)
    return BX
def get_key(key):
    MK = []
    for i in group(key,8):
        MK.append(i)
    key0 = xor(MK[0],FK[0])
    key1 = xor(MK[1],FK[1])
    key2 = xor(MK[2],FK[2])
    key3 = xor(MK[3],FK[3])
    keylist = [key0,key1,key2,key3]
    rk = []
    for i in range(32):
        a = round_function(keylist[i],keylist[i+1],keylist[i+2],keylist[i+3],CK[i],mod='extend')
        keylist.append(a)
        rk.append(a)
    return rk
def get_sm4_ecb(key,input_data,mod):
    data = []
    rk = get_key(key)
    for i in group(input_data,8):
        data.append(i)
    for i in range(32):
        if mod == 'enc':
            ldata = round_function(data[i],data[i+1],data[i+2],data[i+3],rk[i],mod)
        else:
            ldata = round_function(data[i],data[i+1],data[i+2],data[i+3],rk[31-i],mod)
        data.append(ldata)
    out_data = [data[35],data[34],data[33],data[32]]
    out_data = ''.join(out_data)
    return out_data
def get_sm4_cbc(key,input_data,iv,mod):
    rk = get_key(key)
    if mod == 'enc':
        input_data = xor(input_data,iv)
        data = []
        for i in group(input_data,8):
            data.append(i)
        for i in range(32):
            ldata = round_function(data[i],data[i+1],data[i+2],data[i+3],rk[i],mod)
            data.append(ldata)
        out_data = [data[35],data[34],data[33],data[32]]
        out_data = ''.join(out_data)
    else:
        data = []
        for i in group(input_data,8):
            data.append(i)
        for i in range(32):
            ldata = round_function(data[i],data[i+1],data[i+2],data[i+3],rk[31-i],mod)
            data.append(ldata)
        out_data = [data[35],data[34],data[33],data[32]]
        out_data = ''.join(out_data)
        out_data = xor(out_data,iv)
        out_data = '{:032x}'.format(int(out_data, 16))
    return out_data
print(get_sm4_ecb(key = '0123456789abcdeffedcba9876543210', input_data = '0123456789abcdeffedcba9876543210', mod = 'enc'))
print(get_sm4_ecb(key = '0123456789abcdeffedcba9876543210', input_data = '681edf34d206965e86b3e94f536e4246', mod = 'dec'))
print(get_sm4_cbc(key = '0123456789abcdeffedcba9876543210', input_data = '681edf34d206965e86b3e94f536e4246',
                   iv = '0123456789abcdeffedcba9876543210', mod='enc'))
print(get_sm4_cbc(key = '0123456789abcdeffedcba9876543210', input_data = '9ff11dcfd3afaa236c76090babc3bb85',
                   iv = '0123456789abcdeffedcba9876543210', mod='dec'))



import sm4

key = sm4.SM4Key
key = sm4.SM4Key(bytes.fromhex("68677f4e555b4e777b65785b4c726f6f"))
x=[6,7]
s =key.decrypt(bytes.fromhex("5C89EEF56FC54492DBE3AE9CB54F4AF4E7A35E0FFC93FC766CFB29E0162FA567"))


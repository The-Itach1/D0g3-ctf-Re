# #!/usr/bin/env python
# # -*- coding: utf-8 -*-
# import marshal,zlib,base64
#
# out=zlib.decompress(base64.b64decode('eJyNVktv00AQXm/eL0igiaFA01IO4cIVCUGFBBJwqRAckLhEIQmtRfPwI0QIeio/hRO/hJ/CiStH2M/prj07diGRP43Hs9+MZ2fWMxbnP6mux+oK9xVMHPFViLdCTB0xkeKDFEFfTIU4E8KZq8dCvB4UlN3hGEsdddXU9QTLv1eFiGKGM4cKUgsFCNLFH7dFrS9poayFYmIZm1b0gyqxMOwJaU3r6xs9sW1ooakXuRv+un7Q0sIlLVzOCZq/XtsK2oTSYaZlStogXi1HV0iazoN2CV2HZeXqRQ54TlJRb7FUlKyUatISsdzo+P7UU1Gb1POdMruckepGwk9tIXQTftz2yBaT5JQovWvpSa6poJPuqgao+b9l5Aj/R+mLQIP4f6Q8Vb3g/5TB/TJxWGdZr9EQrmn99fwKtTvAZGU7wzS7GNpZpDm2JgCrr8wrmPoo54UqGampFIeS9ojXjc4E2yI06bq/4DRoUAc0nVnng4k6p7Ks0+j/S8z9V+NZ5dhmrJUM/y7JTJeRtnJ2TSYJvsFq3CQt/vnfqmQXt5KlpuRcIvDAmhnn2E0t9BJ3SvB/SfLWhuOWNiNVZ+h28g4wlwUp00w95si43rZ3r6+fUIEdgOZbQAsyFRRvBR6dla8KCzRdslar7WS+a5HFb39peIAmG7uZTHVm17Czxju4m6bayz8e7J40DzqM0jr0bmv9PmPvk6y5z57HU8wdTDHeiUJvBMAM4+0CpoAZ4BPgJeAYEAHmgAUgAHiAj4AVAGORtwd4AVgC3gEmgBBwCPgMWANOAQ8AbwBHgHuAp4D3gLuARwoGmNUizF/j4yDC5BWM1kNvvlxFA8xikRrBxHIUhutFMBlgQoshhPphGAXe/OggKqqb2cibxwuEXjUcQjccxi5eFRL1fDSbKrUhy2CMb2aLyepkegDWsBwPlrVC0/kLHmeCBQ=='))
#
# f=open('out','wb')
#
# f.write(out)
#
# f.close()

import re

with open('1.txt','r') as f:
    line = []
    for i in range(950):
        line.append(f.readline())
l1=[]
for i in line:
    if 'LOAD_CONST' in i :
        l1.append(re.findall(r'\d+',i))
print(l1)
s=''
for i in l1:
    if i[1]!=0:
        s +=chr(int(i[1]))

def ROT_TWO(l):
    a =l.pop()
    b =l.pop()
    l.append(a)
    l.append(b)
    return l

def BINARY_ADD(l):
    a =l.pop()
    b =l.pop()
    # print('{'+a,b,a+b,b+a+'}')
    l.append(b+a)
    return l

# s ="llaC em yP aht notriv lauhcamni !eac Ini npreterP tohty ntybdocese!!! ctihN{noy woc uoc naipmoa eldnur yP nnohttyb doceni euoy rb ria}!napwssro :dorWp gnssadrow...elP  esa yrtaga .ni oD tonurbf etecro)= ."
l3=list(s)
l4=[]
j=0
for i in line:
    if 'LOAD_CONST' in i:
        l4.append(l3[j])
        # print(l4)
        j +=1
    elif 'ROT_TWO' in i:
        l4=ROT_TWO(l4)
    elif 'BINARY_ADD' in i:
        l4=BINARY_ADD(l4)

print(l4)




# with open("1.txt",'r') as f:
#     line = []
#     for i in range(950):
#         line.append(f.readline())
#
# def ROT_TWO(List):
#     a = List.pop()
#     b = List.pop()
#     List.append(a)
#     List.append(b)
#     return List
#
# def BINARY_ADD(List):
#     a = List.pop()
#     b = List.pop()
#     List.append(b+a)
#     return List
#
# cipher = "llaC em yP aht notriv lauhcamni !eac Ini npreterP tohty ntybdocese!!! ctihN{noy woc uoc naipmoa eldnur yP nnohttyb doceni euoy rb ria}!napwssro :dorWp gnssadrow...elP  esa yrtaga .ni oD tonurbf etecro)= ."
# cipher = list(cipher)
#
# s =[]
# j=0
# for i in line:
#     if 'LOAD_CONST' in i and j < len(cipher):
#         s.append(cipher[j])
#         j += 1
#     elif 'ROT_TWO' in i:
#         s = ROT_TWO(s)
#     elif 'BINARY_ADD' in i:
#         s = BINARY_ADD(s)
# print(s)








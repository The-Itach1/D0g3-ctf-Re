import hashlib

table="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/_"
list1=['','BEAC2821ECE8FC5C','ad749265ca7503ef','4386B38FC12C4227','B03ECC45A7EC2DA7', 'BE3C5FFE121734E8']

for j in list1:
    for a in range(30,128):
        for b in range(30,128):
            for c in range(30,128):
                for d in range(30,128):
                    str = chr(a)+chr(b)+chr(c)+chr(d)
                    flag = hashlib.md5(str.encode('utf-8')).hexdigest()
                    if flag[0:16] == j.casefold():
                        print(str, end='')
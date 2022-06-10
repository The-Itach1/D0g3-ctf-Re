import base64
url = "9z2ukkD3Ztxhj+t/S1x1Eg=="
str_url = base64.b64decode(url)

print(str_url)
s='\xf7=\xae\x92@\xf7f\xdca\x8f\xeb\x7fK\\u\x12'
print(len(s))
# import base64
# readfile = open('base.txt','r')
# writefile = open('flag.txt','w')
# txt = readfile.readlines()[0]
# while True:
#     try:
#         txt = base64.b32decode(txt)
#     except:
#         txt = base64.b64decode(txt)
#     finally:
#         print(txt)
#         writefile.write(txt)
#         writefile.write('\n')
# writefile.close()
# readfile.close()
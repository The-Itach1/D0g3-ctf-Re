import base64
date_1 = "you_know_how_to_remove_junk_code"
date_2 = ''
for i in date_1:
    date_2 += chr(ord(i)^0x25)
date = date_2.encode("utf-8")
flag = base64.b64encode(date)  # 被编码的参数必须是二进制数据
print(flag)
from pyDes import des, CBC, PAD_PKCS5
import binascii

# 秘钥
KEY = 'wumansgy'


def des_encrypt(s):
    """
    DES 加密
    :param s: 原始字符串
    :return: 加密后字符串，16进制
    """
    secret_key = KEY
    iv = secret_key
    k = des(secret_key, CBC, iv, pad=None, padmode=PAD_PKCS5)
    en = k.encrypt(s, padmode=PAD_PKCS5)
    return binascii.b2a_hex(en)


def des_descrypt(s):
    """
    DES 解密
    :param s: 加密后的字符串，16进制
    :return:  解密后的字符串
    """
    secret_key = KEY
    iv = secret_key
    k = des(secret_key, CBC, iv, pad=None, padmode=PAD_PKCS5)
    de = k.decrypt(binascii.a2b_hex(s), padmode=PAD_PKCS5)
    return de


s = 'flag'
enc = des_encrypt(s)
print(enc)
des = des_descrypt(enc)
print(des)


from Crypto.Cipher import DES3
import base64

str1 ="o/aWPjNNxMPZDnJlNp0zK5+NLPC4Tv6kqdJqjkL0XkA="
s=base64.b64decode(str1)
c = s
key = b'WelcomeToTheGKCTF2021XXX'
iv = b'1Ssecret'

des = DES3.new(key, DES3.MODE_CBC, iv1)

m = des.decrypt(c)

print(m)
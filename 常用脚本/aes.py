import base64
from Crypto.Cipher import AES
from Crypto import Random
import hashlib
import os
import base64


def encrypt(data, password):
    bs = AES.block_size
    pad = lambda s: s + (bs - len(s) % bs) * chr(bs - len(s) % bs)
    cipher = AES.new(password)
    data = cipher.encrypt(pad(data))
    return (data)


if __name__ == '__main__':
    key = bytearray.fromhex('b22fc60e4fd4544b05111a6121e7b18e')
    key = hashlib.sha256(key).hexdigest()
    key = bytes.fromhex(key)[:16]
    iv = b'\x00' * 16
    cipher = AES.new(key, AES.MODE_CBC, iv)
    f = open('flag.bmp.ctf_crypter', 'rb')
    data = f.read()[:-0x80 - 4]
    de = cipher.decrypt(data)
    d = open('daidai.bmp', 'wb')
    d.write(de)
    d.close()
    f.close()

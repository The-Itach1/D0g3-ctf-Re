//from ida_bytes import *
//patch_byte(0x0040169A, 0x90)

版本1：
#include <idc.idc>

static main(){
    auto addr = 0x401E1F;
    auto i = 0;
    for(i=0;i<0x57E;i++){
        PatchByte(addr + i,Byte(addr + i) ^i);
    }
}

版本2：
import idc
st = 0x401E1f
i = 0
while st <= 0x401E1f+0x57d:
    value = ida_bytes.get_byte(st)
    value ^= (i%256)
    ida_bytes.patch_byte(st, value)
    st += 1
    i += 1

版本3：
import idc
def XorBytes(start, length):
    for i in range(length):
        byte_value = ord(idc.get_bytes(start + i, 1)[0])
        print i, hex(byte_value)
        byte_value = byte_value ^ i
        idc.patch_byte(start + i, byte_value)
XorBytes(0x0000000000401E1F, 0x57D)

版本4：(只适用于ida7.0)
import sys
from idautils import *
from idc import *
import idaapi
if __name__ =="__main__":
    start_addr=0x401E1f
    for i in range(0x57E):
        PatchByte(start_addr+i,Byte(start_addr+i)^i)


import idc
def XorBytes(start, length):
    for i in range(length):
        byte_value = ord(idc.get_bytes(start + i, 1)[0])
        print i, hex(byte_value)
        byte_value = byte_value ^ i
        idc.patch_byte(start + i, byte_value)
XorBytes(0x0000000000401E1F, 0x57D)
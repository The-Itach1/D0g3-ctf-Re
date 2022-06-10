from z3 import *
code=[0xB9, 0x3A, 0xA9, 0xD8, 0x15, 0x8A, 0xE7, 0x42, 0x69, 0x90, 0xCA, 0xA3, 0x4D, 0xD8, 0xD9, 0xC9]

s = Solver()
flag = [BitVec(('x%d' % i), 8) for i in range(16)]
for i in range(16):
    mid=flag[i]
    mid=mid^(mid*2-6)
    mid=mid-i*2
    s.add(mid==code[i])

if s.check() == sat:
     model = s.model()
     str = [chr(model[flag[i]].as_long().real) for i in range(16)]
     print("".join(str))
     exit()
else:
     print("no_sat")
#mBqL!zS6-hLm)XY_


from z3 import *
code=[0x0BC8FF26D43536296,0x520100780530EE16,0x4DC0B5EA935F08EC,0x342B90AFD853F450,
      0x8B250EBCAA2C3681,0x55759F81A2C68AE4]

s = Solver()
flag = [BitVec('flag[%d]' % i, 64) for i in range(6)]
for i in range(6):
  for j in range(64):
    flag[i]=If(flag[i]>=0,flag[i]*2,(flag[i]*2)^0xB0004B7679FA26B3)//z3特有的If
  s.add(flag[i]==code[i])

print(s.check())
m=s.model()
print(m)
# //[flag[4] = 7363777037631763767,
#  flag[3] = 3835203404393046370,
#  flag[1] = 7148951143638579506,
#  flag[2] = 3257850080642543666,
#  flag[0] = 7378644943136451686,
#  flag[5] = 32056]

from z3 import *
flag = [BitVec(f"flag[{i}]", 8) for i in range(18)]
enc=[115, 120, 96, 84, 116, 103, 105, 56, 102, 59, 127, 105, 115, 128, 95, 124, 139, 49]

res=[0]*18
sol = Solver()
k = 0
for i in range(len(flag)):
    res[i] = (flag[i] + i) ^ (k % 3 + 1)
    res[len(flag) - i - 1] = (flag[len(flag) - i - 1] + len(flag) - i - 1) ^ (k % 3 + 1)
    k += 1
for i in range(18):
    sol.add(enc[i] == res[i])
assert sol.check() == sat
mol = sol.model()
print("".join([chr(mol.eval(i).as_long()) for i in flag]))
#py_Trad3_1s_fuNny!



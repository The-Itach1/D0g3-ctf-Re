import base64

base1 = 'QVEJAfHmUYjBac+u8Ph5n9Od16FrICL/X0GvtM4qk7T2z3wNSsyoebilxWKgZpRD='
t = 'PJVqalzl1o1e+Jct6Hct+5MM1vAsa4aScvVM1iYMame='
base =  'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/='
ans = ''

for i in t:
	ans += base[base1.index(i)]
print(ans)
print(base64.b64decode(ans))


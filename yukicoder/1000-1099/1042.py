import math
p,q = map(int,input().split())
ok = 1
ng = 1e19

for i in range (1000):
    md = (ok+ng)/2
    x = md*md
    y = p+q*md*math.log2(md)

    if x < y:
        ok = md
    else:
        ng = md

print(ok)
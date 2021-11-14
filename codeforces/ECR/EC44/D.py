N,H = map(int,input().split())
ans = N
ok = 1
ng = H+1
while ng - ok > 1:
    md = (ok+ng)//2
    K = (md*(md+1))//2
    if K <= N:
        L = N - K
        X = L//md
        if L % md != 0:
            X += 1
        if ans > md+X:
            ans = md + X
        ok = md
    else:
        ng = md
if H*(H+1)//2 > N:
    print(ans)
    exit(0)

ok = H
ng = N
while ng - ok > 1:
    md = (ok+ng)//2
    K = (md*(md+1))//2 + (md*(md-1))//2 - (H*(H-1))//2
    if K <= N:
        L = N - K
        X = md + md - H + L//md 
        if L % md != 0:
            X += 1
        if ans > X:
            ans = X
        ok = md
    else:
        ng = md

print(ans)
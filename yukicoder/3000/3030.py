import random

def miller_rabin(N):
    if N <= 1:
        return False
    if N == 2:
        return True
    M = N-1
    cnt = 0
    while M % 2 == 0:
        M //= 2
        cnt += 1
    v = []
    for i in range(10):
        v.append(random.randint(2,N-1))
    for a in v:
        r = 1
        K = M
        while K > 0:
            if K%2 == 1:
                r *= a
                r %= N

            K //= 2
            a *= a
            a %= N
        if r == 1:
            continue
        for i in range(cnt):
            if r == N-1:
                break
            r *= r
            r %= N
        if r != N-1:
            return False
    return True

n = int(input())
for i in range(n):
    a = int(input())
    b = 0
    if miller_rabin(a):
        b = 1
    print(a,b)

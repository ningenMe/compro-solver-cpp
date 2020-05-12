import decimal
N = int(input())
A = [ decimal.Decimal(input()) for _ in range(N) ]
print('{:.10f}'.format(sum(A)))
n, m, p = map(int, input().split())

nn = 1 << m


def check(i, j, n):
    for k in range(n - 1):
        if ((i >> k) & 1 == 1) and ((j >> k) & 1 == 1) and ((i >> (k + 1)) & 1 == 1) and ((j >> (k + 1)) & 1 == 1):
            return 0
        if ((i >> k) & 1 == 0) and ((j >> k) & 1 == 0) and ((i >> (k + 1)) & 1 == 0) and ((j >> (k + 1)) & 1 == 0):
            return 0
    return 1


def mult(a, b, p):
    n = len(a)
    m = len(b)
    k = len(b[0])
    ans = [[] for i in range(n)]
    for i in range(n):
        for j in range(k):
            ans[i].append(0)
      
    for i in range(n):
        for j in range(k):
            for ii in range(m):
                ans[i][j] = (ans[i][j] + a[i][ii] * b[ii][j]) % p
  #if n == 1:
   # print(ans)
    return ans
  

def superMult(a, b, p):
    r = [[] for i in range(len(a))]
    for i in range(len(a)):
        for j in range(len(a)):
            if i == j:
                r[i].append(1)
            else:
                r[i].append(0)
      
    while b > 0:
        if b % 2 == 1:
            r = mult(r, a, p)
        b //= 2
        a = mult(a, a, p)
      
    return r
  

g = [[] for i in range(nn)]

for i in range(nn):
    for j in range(nn):
        g[i].append(check(i, j, m))

cnt = [[1 for i in range(nn)]]

#for i in range(len(g)):
#  print(g[i])

g = superMult(g, n - 1, p)

#for i in range(nn):
#  print(g[i])

cnt = mult(cnt, g, p)

ans = 0

for i in range(nn):
    ans = (ans + cnt[0][i]) % p
#print(cnt)
print(ans)
